// Fill out your copyright notice in the Description page of Project Settings.


#include "PoolManagerComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../GameMode/InGameMode.h"
#include "../Monster/BaseMonster.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../Components/WaveManagerComponent.h"

UPoolManagerComponent::UPoolManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UPoolManagerComponent::InitPool(const TArray<FName>& InNames, int32 InSpawnCount)
{
	if (!MonsterDataTable)
	{
		return;
	}

	for (const FName& RowName : InNames)
	{
		if (!MonsterPoolMap.Contains(RowName))
		{
			static const FString ContextString(TEXT("Monster Data Context"));

			FMonsterData* Row = MonsterDataTable->FindRow<FMonsterData>(RowName, ContextString);

			if (Row)
			{
				SpawnMonsters(Row->Class, RowName, Row->Stat, InSpawnCount);
			}
		}
	}
}

void UPoolManagerComponent::ReturnToPool(ABaseMonster* InMonster)
{
	if (!InMonster)
	{
		return;
	}

	InMonster->GetCharacterMovement()->StopMovementImmediately();
	InMonster->DisableMonster();

	if (InGameMode)
	{
		InGameMode->WaveManagerComp->DecreaseCurrentAliveCount();
	}
}

ABaseMonster* UPoolManagerComponent::GetFromPool(FName InName)
{
	FMonsterPool* FoundPool = MonsterPoolMap.Find(InName);

	if (FoundPool)
	{
		for (ABaseMonster* Monster : FoundPool->PoolList)
		{
			if (Monster && Monster->IsHidden())
			{
				return Monster;
			}
		}
	}
	
	return nullptr;
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

void UPoolManagerComponent::SpawnMonsters(TSubclassOf<AActor> InSpawnClass, FName InMonsterName, FMonsterStat& InStat, int32 InSpawnCount)
{
	FMonsterPool NewPool;

	for (int32 i = 0; i < InSpawnCount; ++i)
	{
		FTransform SpawnTransform = FTransform::Identity;

		ABaseMonster* NewMonster = GetWorld()->SpawnActorDeferred<ABaseMonster>(
			InSpawnClass,
			SpawnTransform,
			GetOwner(),
			nullptr,
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn
		);

		if (NewMonster)
		{
			NewMonster->SetBaseMonsterStat(InStat);
			NewMonster->DisableMonster();
			NewPool.PoolList.Add(NewMonster);
		}
	}

	MonsterPoolMap.Add(InMonsterName, NewPool);
}

void UPoolManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

