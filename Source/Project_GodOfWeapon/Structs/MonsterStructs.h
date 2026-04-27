// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "MonsterStructs.generated.h"

USTRUCT(BlueprintType)
struct FMonsterPool
{
    GENERATED_BODY()

    FMonsterPool()
    {
    }

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<TObjectPtr<class ABaseMonster>> PoolList;
};

USTRUCT(BlueprintType)
struct FMonsterStat
{
    GENERATED_BODY()

    FMonsterStat()
		: BaseHP(0.0f), BaseDamage(0.0f), Reward(0)
    {
    }

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float BaseHP;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float BaseDamage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Reward;
};

USTRUCT(BlueprintType)
struct FMonsterData : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<class ABaseMonster> Class;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FMonsterStat Stat;
};