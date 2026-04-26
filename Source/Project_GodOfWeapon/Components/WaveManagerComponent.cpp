// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveManagerComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../GameMode/InGameMode.h"
#include "../Player/InGamePlayer.h"
#include "../GodOfWeaponGameInstance.h"

UWaveManagerComponent::UWaveManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UWaveManagerComponent::Init_Implementation(int32 InStage, float InLevelMultiplier, UPoolManagerComponent* InPoolManagerRef)
{
	CurrentStage = InStage;
	LevelMultiplier = InLevelMultiplier;
	PoolManagerRef = InPoolManagerRef;
}

void UWaveManagerComponent::GoNextStage()
{
	UGodOfWeaponGameInstance* GameInstance = Cast<UGodOfWeaponGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GameInstance)
	{
		GameInstance->UpdateStageClear(InGamePlayer->GetPlayerStat(), InGamePlayer->GetCoinCnt(), InGamePlayer->GetEarnedCoinCnt(),InGameMode->GetTotalDamage(), InGameMode->GetTotalMonsterDefeated());

		CurrentStage++;
		if (CurrentStage > MaxWaveCount)
		{
			GameInstance->SetIsVictory(true);
			UGameplayStatics::OpenLevel(GetWorld(), FName("EndingMap"));
		}
		else
		{
			GameInstance->SetCurrentStage(CurrentStage);
			if (CurrentStage % 3 == 0)
			{
				GameInstance->LevelUpPlayer();
			}
			UGameplayStatics::OpenLevel(GetWorld(), FName("InventoryMap"));
		}
	}
}

void UWaveManagerComponent::GoEnding()
{
	UGodOfWeaponGameInstance* GameInstance = Cast<UGodOfWeaponGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GameInstance)
	{
		GameInstance->UpdateStageClear(InGamePlayer->GetPlayerStat(), InGamePlayer->GetCoinCnt(), InGamePlayer->GetEarnedCoinCnt(), InGameMode->GetTotalDamage(), InGameMode->GetTotalMonsterDefeated());

		GameInstance->SetIsVictory(false);
		UGameplayStatics::OpenLevel(GetWorld(), FName("EndingMap"));
	}
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


void UWaveManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

