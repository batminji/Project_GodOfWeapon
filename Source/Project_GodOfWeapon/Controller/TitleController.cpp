// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleController.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraActor.h"
#include "TimerManager.h"
#include "../UI/Title/TitleWidget.h"
#include "../UI/Custom/CustomWidget.h"
#include "../UI/Custom/LevelSettingWidget.h"
#include "../GameMode/TitleGameMode.h"
#include "../GodOfWeaponGameInstance.h"

void ATitleController::BeginPlay()
{
	Super::BeginPlay();

	if (!IsLocalController())
	{
		return;
	}

	AActor* TitleCamera = GetCameraByTag(TEXT("TitleCamera"));
	if (TitleCamera)
	{
		SetViewTarget(TitleCamera);
	}

	ShowTitleUI();
}

void ATitleController::MoveCamera()
{
	AActor* CustomCamera = GetCameraByTag(TEXT("CustomCamera"));
	if (CustomCamera)
	{
		SetViewTargetWithBlend(CustomCamera, 2.0f, VTBlend_EaseInOut, 2.0f);
	}

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ATitleController::OnTimerDelayEnded, 2.0f, false);
}

void ATitleController::CallCameraMoveFinished()
{
	ShowCustomUI();
}

void ATitleController::ShowTitleUI()
{
	if (TitleWidgetClass)
	{
		TitleWidget = CreateAndShowWidget<UTitleWidget>(TitleWidgetClass);
		if (TitleWidget)
		{
			TitleWidget->OnGameStart.AddDynamic(this, &ATitleController::HandleGameStart);

			SetInputMode(FInputModeUIOnly());
			bShowMouseCursor = true;
		}
	}
}

void ATitleController::ShowCustomUI()
{
	if (CustomWidgetClass)
	{
		CustomWidget = CreateAndShowWidget<UCustomWidget>(CustomWidgetClass);
		if (CustomWidget)
		{
			CustomWidget->OnCustomFinished.AddDynamic(this, &ATitleController::HandleCustomFinished);
		}
	}
}

void ATitleController::ShowLevelSettingUI()
{
	if (LevelSettingWidgetClass)
	{

		LevelSettingWidget = CreateAndShowWidget<ULevelSettingWidget>(LevelSettingWidgetClass);
		if (LevelSettingWidget)
		{
			// LevelSettingWidget->OnStartButtonClicked.AddDynamic(this, &ATitleController::HandleEntry);
		}
	}
}

void ATitleController::RemoveTitleUI()
{
	RemoveWidget(TitleWidget);
}

void ATitleController::RemoveCustomUI()
{
	RemoveWidget(CustomWidget);
}

void ATitleController::RemoveLevelSettingUI()
{
	RemoveWidget(LevelSettingWidget);
}

void ATitleController::RequestStartGame()
{
	// 추후 Lobby Map으로 변경
	UGameplayStatics::OpenLevel(GetWorld(), FName("LobbyMap"));
}

AActor* ATitleController::GetCameraByTag(const FName& InTag)
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

void ATitleController::OnTimerDelayEnded()
{
	CallCameraMoveFinished();
}

void ATitleController::HandleGameStart()
{
	RemoveTitleUI();
	MoveCamera();
}

void ATitleController::HandleCustomFinished(FCustomData InCustomData)
{
	UGodOfWeaponGameInstance* GameInstance = Cast<UGodOfWeaponGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		GameInstance->UpdatePlayerCustomData(InCustomData);
	}
	RemoveCustomUI();

	UGameplayStatics::OpenLevel(GetWorld(), FName("LobbyMap"));

	// ShowLevelSettingUI();
}

void ATitleController::HandleEntry(const FSavedItemData& InItemData, EDifficulty InDifficulty)
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
	RemoveLevelSettingUI();

	RequestStartGame();
}
