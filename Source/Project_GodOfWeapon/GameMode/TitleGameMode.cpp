// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "../Controller/TitleController.h"

void ATitleGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void ATitleGameMode::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);

    ATitleController* TitleController = Cast<ATitleController>(NewPlayer);
    if (TitleController)
    {
        TitleController->ClientShowTitleUI();
    }
}
