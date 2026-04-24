// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerStructs.generated.h"

USTRUCT(BlueprintType)
struct FCustomizeData
{
    GENERATED_BODY()

    FCustomizeData() 
        : HeadNumber(15), ChestNumber(1), HandsNumber(1), LegsNumber(5), FootNumber(1)
    {}

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 HeadNumber;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 ChestNumber;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 HandsNumber;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 LegsNumber;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 FootNumber;
};

USTRUCT(BlueprintType)
struct FPlayerLevel : public FTableRowBase
{
    GENERATED_BODY()

    FPlayerLevel()
        : Multiplier(1.0f)
    {
    }

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Multiplier;
};