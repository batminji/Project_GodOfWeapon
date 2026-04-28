// Fill out your copyright notice in the Description page of Project Settings.


#include "EndGameMode.h"
#include "../GodOfWeaponGameInstance.h"

void AEndGameMode::BeginPlay()
{
	Super::BeginPlay();
	GameInstance = Cast<UGodOfWeaponGameInstance>(GetGameInstance());
}
