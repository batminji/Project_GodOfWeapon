// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "../Controller/TitleController.h"
#include "../UI/Title/TitleWidget.h"

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
