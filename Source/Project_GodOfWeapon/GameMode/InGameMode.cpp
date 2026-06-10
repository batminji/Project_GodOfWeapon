// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "InGameStateBase.h"
#include "../Player/PlayerStateBase.h"
#include "../Components/WaveManagerComponent.h"
#include "../Components/PoolManagerComponent.h"
#include "../GodOfWeaponGameInstance.h"
#include "../Player/InGamePlayer.h"

AInGameMode::AInGameMode()
{
	bUseSeamlessTravel = true;

	GameStateClass = AInGameStateBase::StaticClass();
	PlayerStateClass = APlayerStateBase::StaticClass();

	WaveManagerComp = CreateDefaultSubobject<UWaveManagerComponent>(TEXT("WaveManagerComp"));
	PoolManagerComp = CreateDefaultSubobject<UPoolManagerComponent>(TEXT("PoolManagerComp"));
}

void AInGameMode::PostLogin(APlayerController* InNewPlayer)
{
	Super::PostLogin(InNewPlayer);

	if (!GameInstance)
	{
		return;
	}

	APlayerStateBase* PlayerState = InNewPlayer->GetPlayerState<APlayerStateBase>();
	if (!PlayerState)
	{
		return;
	}

	PlayerState->CustomData = GameInstance->GetPlayerCustomData();
}

void AInGameMode::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	Super::HandleStartingNewPlayer_Implementation(NewPlayer);

	APlayerStateBase* PlayerState = NewPlayer->GetPlayerState<APlayerStateBase>();
	AInGamePlayer* Player = Cast<AInGamePlayer>(NewPlayer->GetPawn());
	if (!PlayerState || !Player) return;

	Player->UpdatePlayerStat(PlayerState->PlayerStat, PlayerState->PlayerCoin);
	Player->UpdatePlayerCustom(PlayerState->CustomData);

	InGamePlayer = Player;
}

void AInGameMode::BeginPlay()
{
	Super::BeginPlay();

	Init();
	// UpdatePlayerStat();
	// Login 에서 호출할 것
	SpawnItems();

	AInGameStateBase* InGameState = GetGameState<AInGameStateBase>();
	if (InGameState && GameInstance)
	{
		InGameState->LevelMultiplier = GameInstance->GetLevelMultiplier();
	}

	if (WaveManagerComp)
	{
		
		if (InGameState)
		{
			WaveManagerComp->Init(InGameState->CurrentStage, InGameState->LevelMultiplier, PoolManagerComp);
		}

		WaveManagerComp->StartGame();
	}
}

void AInGameMode::Init()
{
	GameInstance = Cast<UGodOfWeaponGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
}