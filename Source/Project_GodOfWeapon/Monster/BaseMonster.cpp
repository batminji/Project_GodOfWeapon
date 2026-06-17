// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseMonster.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../Controller/MonsterAIController.h"
#include "../GameMode/InGameMode.h"
#include "../Components/PoolManagerComponent.h"
#include "Net/UnrealNetwork.h"

ABaseMonster::ABaseMonster()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
}

void ABaseMonster::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ABaseMonster, bIsDead);
	DOREPLIFETIME(ABaseMonster, bIsSpawning);
}

void ABaseMonster::MulticastShowCoin_Implementation()
{
	CreateCoinActors(CurrentMonsterStat.Reward);
}

void ABaseMonster::MulticastShowDamage_Implementation(int32 InDamage)
{
	CreateDamageTextWidget(InDamage);
}

void ABaseMonster::MulticastOnDied_Implementation()
{
	bIsDead = true;

	GetCharacterMovement()->StopMovementImmediately();
	SetActorEnableCollision(false);
	StopAnimMontage();
}

void ABaseMonster::DisableMonster()
{
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	PrimaryActorTick.SetTickFunctionEnable(false);

	bIsDead = false;
	bIsSpawning = false;

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

	if (!HasAuthority())
	{
		return;
	}

	if (InGameMode)
	{
		InGameMode->PoolManagerComp->ReturnToPool(this);
	}
}

void ABaseMonster::DieMonster()
{
	bIsDead = true;

	GetCharacterMovement()->StopMovementImmediately();
	SetActorEnableCollision(false);
	StopAnimMontage();

	if (AIController)
	{
		AIController->StopAI();
	}

	if (InGameMode)
	{
		InGameMode->AddTotalMonsterDefeated(1);
	}

	MulticastOnDied();

	MulticastShowCoin();
}

void ABaseMonster::ApplyMonsterDamage(float InDamage)
{
	if (!HasAuthority())
	{
		return;
	}

	int32 Damage = FMath::TruncToInt(InDamage);

	MulticastShowDamage(Damage);

	if (InGameMode)
	{
		InGameMode->AddTotalDamage(Damage);
	}
	UpdateMonsterHP(Damage);
}

void ABaseMonster::OnRep_IsDead()
{
	if (bIsDead)
	{
		SetActorEnableCollision(false);
		GetCharacterMovement()->StopMovementImmediately();
		StopAnimMontage();
	}
	else
	{
		SetActorEnableCollision(true);
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

