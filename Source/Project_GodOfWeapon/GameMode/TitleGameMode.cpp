// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "../Controller/TitleController.h"
#include "../UI/Title/TitleWidget.h"
#include "../UI/Custom/CustomWidget.h"
#include "../UI/Custom/LevelSettingWidget.h"
#include "../GodOfWeaponGameInstance.h"

void ATitleGameMode::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController =
		UGameplayStatics::GetPlayerController(GetWorld(), 0);
	TitleController = Cast<ATitleController>(PlayerController);

	if (TitleController)
	{
		TitleController->OnCameraMoveFinished.AddDynamic(this, &ATitleGameMode::HandleMoveCameraEnded);
	}

	if (TitleWidgetClass)
	{
		TitleWidget = CreateWidget<UTitleWidget>(GetWorld(), TitleWidgetClass);
		if (TitleWidget)
		{
			TitleWidget->AddToViewport();

			TitleWidget->OnGameStart.AddDynamic(this, &ATitleGameMode::HandleGameStart);
		}
	}
}

void ATitleGameMode::HandleMoveCameraEnded()
{
	if (CustomWidgetClass)
	{
		CustomWidget = CreateWidget<UCustomWidget>(GetWorld(), CustomWidgetClass);
		if (CustomWidget)
		{
			CustomWidget->AddToViewport();

			CustomWidget->OnCustomFinished.AddDynamic(this, &ATitleGameMode::HandleCustomFinished);
		}
	}
}

void ATitleGameMode::HandleGameStart()
{
	if (TitleWidget)
	{
		TitleWidget->RemoveFromParent();
		TitleWidget = nullptr;
	}

	if (TitleController)
	{
		TitleController->MoveCamera();
	}
}

void ATitleGameMode::HandleCustomFinished(FCustomData InCustomData)
{
	UGodOfWeaponGameInstance* GI = Cast<UGodOfWeaponGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GI)
	{
		GI->UpdatePlayerCustomData(InCustomData);
		// UE_LOG(LogTemp, Log, TEXT("Custom Data Updated: Head: %d, Chest: %d, Hands: %d, Legs: %d, Foot: %d"), InCustomData.HeadNumber, InCustomData.ChestNumber, InCustomData.HandsNumber, InCustomData.LegsNumber, InCustomData.FootNumber);
	}

	CreateLevelWidget();
}

void ATitleGameMode::HandleEntry(const FSavedItemData& InItemData, EDifficulty InDifficulty)
{
	UpdateItemAndLevel(InItemData, InDifficulty);

	UGameplayStatics::OpenLevel(GetWorld(), FName("InGameMap"));
}

void ATitleGameMode::CreateLevelWidget()
{
	if (LevelSettingWidgetClass)
	{
		LevelSettingWidget = CreateWidget<ULevelSettingWidget>(GetWorld(), LevelSettingWidgetClass);

		if (LevelSettingWidget)
		{
			LevelSettingWidget->AddToViewport();
			// UE_LOG(LogTemp, Log, TEXT("Level Setting Widget Created"));
			LevelSettingWidget->OnStartButtonClicked.AddDynamic(this, &ATitleGameMode::HandleEntry);
		}
	}
}

void ATitleGameMode::UpdateItemAndLevel(const FSavedItemData& InItemData, const EDifficulty InDifficulty)
{
	UGodOfWeaponGameInstance* GI = Cast<UGodOfWeaponGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GI)
	{
		GI->GetInventoryData().Add(InItemData);

		GI->SetDifficulty(InDifficulty);

		switch (InDifficulty)
		{
		case EDifficulty::Easy:
		{
			GI->SetLevelMultiplier(0.8f);
			break;
		}
		case EDifficulty::Normal:
		{
			GI->SetLevelMultiplier(1.0f);
			break;
		}
		case EDifficulty::Hard:
		{
			GI->SetLevelMultiplier(1.5f);
			break;
		}
		default:
			break;
		}
	}

	if (LevelSettingWidget)
	{
		LevelSettingWidget->RemoveFromParent();
		LevelSettingWidget = nullptr;
	}
}
