// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseMonster.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../Controller/MonsterAIController.h"
#include "../GameMode/InGameMode.h"
#include "../Components/PoolManagerComponent.h"

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
	UpdateBBSpawning();

	if (AIController)
	{
		AIController->RunAI();
	}
}

void ABaseMonster::EndSpawning()
{
	bIsSpawning = false;
	UpdateBBSpawning();
}

void ABaseMonster::EndDying()
{
	bIsDead = false;

	if (InGameMode)
	{
		InGameMode->PoolManagerComp->ReturnToPool(this);
	}
}

void ABaseMonster::DieMonster()
{
	CreateCoinActors(CurrentMonsterStat.Reward);

	bIsDead = true;

	GetCharacterMovement()->StopMovementImmediately();
	SetActorEnableCollision(false);

	if (AIController)
	{
		AIController->StopAI();
	}

	if (InGameMode)
	{
		InGameMode->AddTotalMonsterDefeated(1);
	}
}

void ABaseMonster::ApplyMonsterDamage(float InDamage)
{
	int32 Damage = FMath::TruncToInt(InDamage);
	
	CreateDamageTextWidget(Damage);
	if (InGameMode)
	{
		InGameMode->AddTotalDamage(Damage);
	}
	UpdateMonsterHP(Damage);
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

void ABaseMonster::UpdateBBSpawning()
{
	if(AIController)
	{
		if (AIController->GetBlackboardComponent())
		{
			AIController->GetBlackboardComponent()->SetValueAsBool(TEXT("bIsSpawning"), bIsSpawning);
		}
	}
}

void ABaseMonster::UpdateMonsterHP(int32 InDamage)
{
	CurrentMonsterStat.BaseHP -= InDamage;
	if (CurrentMonsterStat.BaseHP <= 0)
	{
		DieMonster();
	}
}

void ABaseMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

