// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseMonster.h"
#include "../Controller/MonsterAIController.h"

ABaseMonster::ABaseMonster()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ABaseMonster::DisableMonster()
{
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	PrimaryActorTick.SetTickFunctionEnable(false);

	if (AIController)
	{
		AIController->StopAI();
	}
}

void ABaseMonster::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseMonster::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	AIController = Cast<AMonsterAIController>(NewController);
}

void ABaseMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

