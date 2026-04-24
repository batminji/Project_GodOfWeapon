// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "../Controller/TitleController.h"
#include "../UI/Title/TitleWidget.h"
#include "../UI/Custom/CustomWidget.h"
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
	}
}
