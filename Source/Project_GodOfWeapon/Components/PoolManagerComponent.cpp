// Fill out your copyright notice in the Description page of Project Settings.


#include "PoolManagerComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../GameMode/InGameMode.h"

UPoolManagerComponent::UPoolManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UPoolManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	SetGameMode();
}

void UPoolManagerComponent::SetGameMode()
{
	InGameMode = Cast<AInGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
}

void UPoolManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

