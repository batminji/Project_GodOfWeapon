// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StageEnums.generated.h"

UENUM(BlueprintType)
enum class EDifficulty : uint8
{
    Easy    UMETA(DisplayName = "Easy"),
    Normal  UMETA(DisplayName = "Normal"),
    Hard    UMETA(DisplayName = "Hard")
};
