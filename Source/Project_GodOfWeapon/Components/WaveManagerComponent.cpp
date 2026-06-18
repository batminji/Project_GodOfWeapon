// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveManagerComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../GameMode/InGameMode.h"
#include "../GameMode/InGameStateBase.h"
#include "../Player/InGamePlayer.h"
#include "../Player/PlayerStateBase.h"
#include "../GodOfWeaponGameInstance.h"
#include "../Structs/WaveStructs.h"
#include "../Components/PoolManagerComponent.h"
#include "GameFramework/PlayerState.h"
#include "Engine/DataTable.h"

UWaveManagerComponent::UWaveManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UWaveManagerComponent::Init(int32 InStage, float InLevelMultiplier, UPoolManagerComponent* InPoolManagerRef)
{
	CurrentStage = InStage;
	LevelMultiplier = InLevelMultiplier;
	PoolManagerRef = InPoolManagerRef;

	FName RowName = FName(*FString::FromInt(CurrentStage));
	FWaveData* FindRow = WaveDataTable->FindRow<FWaveData>(RowName, TEXT("WaveData"));

	if(FindRow)
	{
		SpawnMonsterNames = FindRow->SpawnMonsters;
		StatMultiplier = FindRow->StatMultiplier;
		SpawnInterval = FindRow->SpawnInterval;
		WaveTimer = FindRow->Time;
		MaxAliveCount = FindRow->SpawnCount;
	}

	if(PoolManagerRef)
	{
		PoolManagerRef->InitPool(SpawnMonsterNames, MaxAliveCount);
	}
}

void UWaveManagerComponent::GoNextStage()
{
	if (!GetOwner()->HasAuthority())
	{
		return;
	}

	AInGameStateBase* GameState = Cast<AInGameStateBase>(UGameplayStatics::GetGameState(GetWorld()));
	if (!GameState)
	{
		return;
	}

	UpdatePlayerStatForNextStage(GameState);
	UpdateStage(GameState);
}

void UWaveManagerComponent::GoEnding()
{
	if (!GetOwner()->HasAuthority())
	{
		return;
	}

	AInGameStateBase* GameState = Cast<AInGameStateBase>(UGameplayStatics::GetGameState(GetWorld()));
	if (!GameState)
	{
		return;
	}

	UpdatePlayerStatForNextStage(GameState);

	UGodOfWeaponGameInstance* GameInstance = Cast<UGodOfWeaponGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GameInstance)
	{
		GameInstance->SetIsVictory(false);
		GameInstance->ResultStage = CurrentStage;
		for (APlayerState* PS : GameState->PlayerArray)
		{
			APlayerStateBase* PlayerState = Cast<APlayerStateBase>(PS);
			if (!PlayerState)
			{
				continue;
			}
			GameInstance->ResultEarnedCoin += PlayerState->PlayerEarnedCoin;
			GameInstance->ResultTotalDamage += PlayerState->TotalDamage;
			GameInstance->ResultTotalMonsterDefeated += PlayerState->TotalMonsterDefeated;
		}
	}

	GetWorld()->ServerTravel("/Game/Maps/EndingMap?listen");
}

void UWaveManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	SetPlayer();
	SetGameMode();
}

void UWaveManagerComponent::SetPlayer_Implementation()
{
	InGamePlayer = Cast<AInGamePlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}

void UWaveManagerComponent::SetGameMode()
{
	InGameMode = Cast<AInGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
}

void UWaveManagerComponent::UpdatePlayerStatForNextStage(AInGameStateBase* InGameState)
{
	// Player State Áý°è
	for (APlayerState* PS : InGameState->PlayerArray)
	{
		APlayerStateBase* TempPlayerState = Cast<APlayerStateBase>(PS);
		if (!TempPlayerState)
		{
			continue;
		}

		AInGamePlayer* Player = Cast<AInGamePlayer>(TempPlayerState->GetPawn());
		if (!Player)
		{
			continue;
		}

		TempPlayerState->PlayerEarnedCoin += Player->GetEarnedCoinCnt();
		TempPlayerState->TotalDamage += InGameMode->GetTotalDamage();
		TempPlayerState->TotalMonsterDefeated += InGameMode->GetTotalMonsterDefeated();
	}
}

void UWaveManagerComponent::UpdateStage(AInGameStateBase* InGameState)
{
	CurrentStage++;

	if (CurrentStage > MaxWaveCount)
	{
		UGodOfWeaponGameInstance* GameInstance = Cast<UGodOfWeaponGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
		if (GameInstance)
		{
			GameInstance->SetIsVictory(true);
			GameInstance->ResultStage = CurrentStage;
			for (APlayerState* PS : InGameState->PlayerArray)
			{
				APlayerStateBase* PlayerState = Cast<APlayerStateBase>(PS);
				if (!PlayerState)
				{
					continue;
				}
				GameInstance->ResultEarnedCoin += PlayerState->PlayerEarnedCoin;
				GameInstance->ResultTotalDamage += PlayerState->TotalDamage;
				GameInstance->ResultTotalMonsterDefeated += PlayerState->TotalMonsterDefeated;
			}
			GetWorld()->ServerTravel("/Game/Maps/EndingMap?listen");
		}
	}
	else
	{
		InGameMode->SetCurrentStage(CurrentStage);

		if (CurrentStage % 3 == 0)
		{
			LevelUpAllPlayers(InGameState);
		}

		GetWorld()->ServerTravel("/Game/Maps/InventoryMap?listen");
	}
}

void UWaveManagerComponent::LevelUpAllPlayers(AInGameStateBase* InGameState)
{
	if (!InGameState)
	{
		return;
	}

	UGodOfWeaponGameInstance* GameInstance = Cast<UGodOfWeaponGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (!GameInstance) return;

	FName RowName = FName(*FString::FromInt(CurrentStage));
	FPlayerLevel* Row = GameInstance->GetPlayerLevelDataTable()->FindRow<FPlayerLevel>(RowName, TEXT("LevelUpAllPlayers"));
	if (!Row) return;

	for (APlayerState* PS : InGameState->PlayerArray)
	{
		APlayerStateBase* GodPS = Cast<APlayerStateBase>(PS);
		if (!GodPS) continue;

		GodPS->ApplyStatMultiplier(Row->Multiplier);

		AInGamePlayer* Player = Cast<AInGamePlayer>(GodPS->GetPawn());
		if (Player)
		{
			Player->ClientExpandInventory();
		}
	}
}


void UWaveManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

