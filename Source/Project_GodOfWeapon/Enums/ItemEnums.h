// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemEnums.generated.h"

UENUM(BlueprintType)
enum class EItemState : uint8
{
    Idle        UMETA(DisplayName = "Idle"),
    Approach    UMETA(DisplayName = "Approach"),
    Attacking   UMETA(DisplayName = "Attacking"),
    Returning   UMETA(DisplayName = "Returning"),
    Cooldown    UMETA(DisplayName = "Cooldown")
};
