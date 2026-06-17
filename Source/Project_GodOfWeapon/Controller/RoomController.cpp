// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomController.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

#include "../UI/Room/RoomHUDWidget.h"
#include "Camera/CameraActor.h"
#include "../Player/RoomCharacter.h"
#include "../GodOfWeaponGameInstance.h"

ARoomController::ARoomController()
{
	bAutoManageActiveCameraTarget = false;
}

void ARoomController::BeginPlay()
{
	Super::BeginPlay();

	AActor* MainCamera = GetCameraByTag(TEXT("MainCamera"));
	if (MainCamera)
	{
		SetViewTarget(MainCamera);
	}
	
	if(!IsLocalController())
	{
		return;
	}

	ShowRoomHUD();
}

void ARoomController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ARoomController, MyRoomCharacter);
}

void ARoomController::SetMyRoomCharacter(ARoomCharacter* InCharacter)
{
	MyRoomCharacter = InCharacter;

	// 호스트인 경우 OnRep이 자동 호출되지 않으므로 직접 호출
	if (GetNetMode() == NM_ListenServer && IsLocalController())
	{
		TrySendCustomData();
	}
}

void ARoomController::HandleEntry(const FSavedItemData& InItemData, EDifficulty InDifficulty)
{
	ServerStartGameWithData(InItemData, InDifficulty);
}

void ARoomController::ServerSendCustomData_Implementation(const FCustomData& InCustomData)
{
	if (MyRoomCharacter)
	{
		MyRoomCharacter->CustomData = InCustomData;
		MyRoomCharacter->UpdatePlayerCustom(InCustomData);
	}
}

void ARoomController::ShowRoomHUD()
{
	if (RoomHUDWidgetClass)
	{
		URoomHUDWidget* RoomHUD = CreateWidget<URoomHUDWidget>(this, RoomHUDWidgetClass);
		if (RoomHUD)
		{
			RoomHUD->AddToViewport();
			RoomHUD->OnStartButtonClicked.AddDynamic(this, &ARoomController::HandleEntry);
			SetInputMode(FInputModeGameAndUI());
			bShowMouseCursor = true;
		}
	}
}

AActor* ARoomController::GetCameraByTag(const FName& InTag)
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACameraActor::StaticClass(), FoundActors);

	for (AActor* Actor : FoundActors)
	{
		if (Actor->ActorHasTag(InTag))
		{
			return Actor;
		}
	}

	return nullptr;
}

void ARoomController::OnRep_MyRoomCharacter()
{
	TrySendCustomData();
}

void ARoomController::TrySendCustomData()
{
	if (!IsLocalController() || !MyRoomCharacter)
	{
		return;
	}

	UGodOfWeaponGameInstance* GameInstance = Cast<UGodOfWeaponGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		ServerSendCustomData(GameInstance->GetPlayerCustomData());
	}
}

void ARoomController::ExecuteServerTravel()
{
	GetWorld()->ServerTravel(TEXT("/Game/Maps/InGameMap?listen"));
}

void ARoomController::ClientUpdateGameInstanceData_Implementation(const FSavedItemData& InItemData, EDifficulty InDifficulty)
{
	UGodOfWeaponGameInstance* GameInstance = Cast<UGodOfWeaponGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		GameInstance->GetInventoryData().Add(InItemData);
		GameInstance->SetDifficulty(InDifficulty);

		switch (InDifficulty)
		{
		case EDifficulty::Easy:
			GameInstance->SetLevelMultiplier(0.8f);
			break;
		case EDifficulty::Normal:
			GameInstance->SetLevelMultiplier(1.0f);
			break;
		case EDifficulty::Hard:
			GameInstance->SetLevelMultiplier(1.5f);
			break;
		}
	}
}

void ARoomController::ServerStartGameWithData_Implementation(const FSavedItemData& InItemData, EDifficulty InDifficulty)
{
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		ARoomController* PC = Cast<ARoomController>(It->Get());
		if (PC)
		{
			PC->ClientUpdateGameInstanceData(InItemData, InDifficulty);
		}
	}

	FTimerHandle TravelTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TravelTimerHandle, this, &ARoomController::ExecuteServerTravel, 0.2f, false);
}
