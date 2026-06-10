// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomCharacter.h"
#include "Net/UnrealNetwork.h"

ARoomCharacter::ARoomCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
}

void ARoomCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ARoomCharacter, CustomData);
}

void ARoomCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARoomCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARoomCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ARoomCharacter::OnRep_CustomData()
{
	UpdatePlayerCustom(CustomData);
}

