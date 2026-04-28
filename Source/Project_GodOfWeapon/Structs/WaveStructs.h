// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WaveStructs.generated.h"

USTRUCT(BlueprintType)
struct FWaveData : public FTableRowBase
{
    GENERATED_BODY()

    FWaveData()
        : StageNum(0), SpawnCount(0), Time(0.0f), SpawnInterval(0.0f), StatMultiplier(0.0f)
    {
	}

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 StageNum;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FName> SpawnMonsters;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 SpawnCount;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Time;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float SpawnInterval;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float StatMultiplier;
};