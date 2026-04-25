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

	TitleWidget = CreateAndShowWidget<UTitleWidget>(TitleWidgetClass);
	if (TitleWidget)
	{
		TitleWidget->OnGameStart.AddDynamic(this, &ATitleGameMode::HandleGameStart);
	}
}

void ATitleGameMode::HandleMoveCameraEnded()
{
	CustomWidget = CreateAndShowWidget<UCustomWidget>(CustomWidgetClass);
	if (CustomWidget)
	{
		CustomWidget->OnCustomFinished.AddDynamic(this, &ATitleGameMode::HandleCustomFinished);
	}
}

void ATitleGameMode::HandleGameStart()
{
	RemoveWidget(TitleWidget);

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
	}
	RemoveWidget(CustomWidget);

	CreateLevelWidget();
}

void ATitleGameMode::HandleEntry(const FSavedItemData& InItemData, EDifficulty InDifficulty)
{
	UpdateItemAndLevel(InItemData, InDifficulty);

	RemoveWidget(LevelSettingWidget);

	UGameplayStatics::OpenLevel(GetWorld(), FName("InGameMap"));
}

void ATitleGameMode::CreateLevelWidget()
{
	LevelSettingWidget = CreateAndShowWidget<ULevelSettingWidget>(LevelSettingWidgetClass);
	if (LevelSettingWidget)
	{
		LevelSettingWidget->OnStartButtonClicked.AddDynamic(this, &ATitleGameMode::HandleEntry);
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
}
