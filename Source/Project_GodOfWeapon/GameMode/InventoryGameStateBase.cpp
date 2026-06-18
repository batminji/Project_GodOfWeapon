// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryGameStateBase.h"
#include "Net/UnrealNetwork.h"

void AInventoryGameStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AInventoryGameStateBase, LeftTime);
}

void AInventoryGameStateBase::BeginPlay()
{
	Super::BeginPlay();

	Init();
}

void AInventoryGameStateBase::Init()
{
	LeftTime = 30;
}