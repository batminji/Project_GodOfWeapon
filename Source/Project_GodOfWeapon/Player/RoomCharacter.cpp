// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomCharacter.h"

ARoomCharacter::ARoomCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

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

