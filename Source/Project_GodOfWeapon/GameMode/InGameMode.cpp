// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "../Components/WaveManagerComponent.h"
#include "../Components/PoolManagerComponent.h"
#include "../GodOfWeaponGameInstance.h"
#include "../Player/InGamePlayer.h"

AInGameMode::AInGameMode()
{
	WaveManagerComponent = CreateDefaultSubobject<UWaveManagerComponent>(TEXT("WaveManagerComponent"));
	PoolManagerComponent = CreateDefaultSubobject<UPoolManagerComponent>(TEXT("PoolManagerComponent"));
}

void AInGameMode::BeginPlay()
{
	Super::BeginPlay();

	Init();
	UpdatePlayerStat();
	SpawnItems();
}

void AInGameMode::Init()
{
	GameInstance = Cast<UGodOfWeaponGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	InGamePlayer = Cast<AInGamePlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

void AInGameMode::UpdatePlayerStat()
{
	if (GameInstance && InGamePlayer)
	{
		InGamePlayer->UpdatePlayerStat(GameInstance->GetPlayerStat(), GameInstance->GetPlayerCoin());

		InGamePlayer->UpdatePlayerCustom(GameInstance->GetPlayerCustomData());
	}
}
