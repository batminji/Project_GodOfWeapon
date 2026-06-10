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
}

void ARoomController::HandleEntry(const FSavedItemData& InItemData, EDifficulty InDifficulty)
{
	UGodOfWeaponGameInstance* GameInstance = Cast<UGodOfWeaponGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		GameInstance->GetInventoryData().Add(InItemData);
		GameInstance->SetDifficulty(InDifficulty);
		switch (InDifficulty)
		{
		case EDifficulty::Easy:
		{
			GameInstance->SetLevelMultiplier(0.8f);
		}
		break;
		case EDifficulty::Normal:
		{
			GameInstance->SetLevelMultiplier(1.0f);
		}
		break;
		case EDifficulty::Hard:
		{
			GameInstance->SetLevelMultiplier(1.5f);
		}
		break;
		default:
			break;
		}
	}

	// Game Start
	ServerStartGame();
}

void ARoomController::ServerStartGame_Implementation()
{
	GetWorld()->ServerTravel(TEXT("/Game/Maps/InGameMap?listen"));
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
