// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveManagerComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../GameMode/InGameMode.h"
#include "../Player/InGamePlayer.h"

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

void UWaveManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	SetPlayer();
	SetGameMode();
}

void UWaveManagerComponent::SetPlayer_Implementation()
{
	Player = Cast<AInGamePlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}

void UWaveManagerComponent::SetGameMode()
{
	InGameMode = Cast<AInGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
}


void UWaveManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

