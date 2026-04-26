// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseMonster.h"
#include "Kismet/GameplayStatics.h"
#include "../Controller/MonsterAIController.h"
#include "../GameMode/InGameMode.h"

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

void ABaseMonster::EnableMonster_Implementation(float InStatMultiplier, float InLevelMultiplier)
{
	CurrentMonsterStat.BaseHP = BaseMonsterStat.BaseHP * InStatMultiplier * InLevelMultiplier;
	CurrentMonsterStat.BaseDamage = BaseMonsterStat.BaseDamage * InStatMultiplier * InLevelMultiplier;
	CurrentMonsterStat.Reward = FMath::TruncToInt(BaseMonsterStat.Reward * InLevelMultiplier);

	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	PrimaryActorTick.SetTickFunctionEnable(true);

	bIsDead = false;
	bIsSpawning = true;

	if (AIController)
	{
		AIController->RunAI();
	}
}

void ABaseMonster::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseMonster::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	SetGameMode();
	SetAIController();	
}

void ABaseMonster::SetGameMode()
{
	InGameMode = Cast<AInGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
}

void ABaseMonster::SetAIController()
{
	AIController = Cast<AMonsterAIController>(GetController());
}

void ABaseMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

