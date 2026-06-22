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
#include "InGameStateBase.h"
#include "../Controller/InGameController.h"

AInGameMode::AInGameMode()
{
	bUseSeamlessTravel = true;
	PrimaryActorTick.bCanEverTick = true;

	GameStateClass = AInGameStateBase::StaticClass();
	PlayerStateClass = APlayerStateBase::StaticClass();

	WaveManagerComp = CreateDefaultSubobject<UWaveManagerComponent>(TEXT("WaveManagerComp"));
	PoolManagerComp = CreateDefaultSubobject<UPoolManagerComponent>(TEXT("PoolManagerComp"));
}

void AInGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	UpdateGameStateLeftTime();
}

void AInGameMode::PostLogin(APlayerController* InNewPlayer)
{
	Super::PostLogin(InNewPlayer);
}

void AInGameMode::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	Super::HandleStartingNewPlayer_Implementation(NewPlayer);
}

void AInGameMode::BeginPlay()
{
	Super::BeginPlay();

	Init();

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

	UpdateGameStateCurrentStage();
}

void AInGameMode::Init()
{
	GameInstance = Cast<UGodOfWeaponGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
}

void AInGameMode::UpdateGameStateLeftTime()
{
	AInGameStateBase* InGameState = GetGameState<AInGameStateBase>();
	if (InGameState)
	{
		InGameState->LeftTime = LeftTime;
	}
}

void AInGameMode::UpdateGameStateCurrentStage()
{
	AInGameStateBase* InGameState = GetGameState<AInGameStateBase>();
	if (InGameState)
	{
		InGameState->CurrentStage = CurrentStage;
	}
}

void AInGameMode::OnPlayerSaveCompleted(AInGameController* PlayerController)
{
	if (!PlayerController || SavedPlayers.Contains(PlayerController))
	{
		return;
	}

	SavedPlayers.Add(PlayerController);

	if (SavedPlayers.Num() >= GetNumPlayers())
	{
		GetWorld()->ServerTravel("/Game/Maps/InventoryMap?listen");
	}
}

void AInGameMode::StartSaveSequence()
{
	SavedPlayers.Empty();

	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		AInGameController* InGameController = Cast<AInGameController>(*It);
		if (InGameController)
		{
			InGameController->S2C_SavePlayerStateToInstance();
		}
	}
}
