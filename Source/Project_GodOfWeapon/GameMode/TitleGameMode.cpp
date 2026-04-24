// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "../Controller/TitleController.h"

void ATitleGameMode::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController =
		UGameplayStatics::GetPlayerController(GetWorld(), 0);
	TitleController = Cast<ATitleController>(PlayerController);

	if (TitleController)
	{
		TitleController->OnMoveCameraEnded.AddDynamic(this, &ATitleGameMode::CreateCustomWidget);
	}
}

void ATitleGameMode::CreateCustomWidget()
{
}
