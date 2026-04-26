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
		UE_LOG(LogTemp, Log, TEXT("Running AI for monster: %s"), *GetName());
		AIController->RunAI();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController is null for monster: %s"), *GetName());
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
	AIController = Cast<AMonsterAIController>(NewController);
}

void ABaseMonster::SetGameMode()
{
	InGameMode = Cast<AInGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
}

void ABaseMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

