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

	AInGamePlayer* Player = Cast<AInGamePlayer>(InNewPlayer->GetPawn());
	if (Player)
	{
		Player->UpdatePlayerStat(PlayerState->PlayerStat, PlayerState->PlayerCoin);
		Player->UpdatePlayerCustom(PlayerState->CustomData);
	}
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

	if (InGameMainWidgetClass)
	{
		InGameMainWidget = CreateWidget<UUserWidget>(GetWorld(), InGameMainWidgetClass);
		if (InGameMainWidget)
		{
			InGameMainWidget->AddToViewport();
		}
	}
}

void AInGameMode::Init()
{
	GameInstance = Cast<UGodOfWeaponGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
}