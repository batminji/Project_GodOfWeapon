// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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