// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerStatStructure.generated.h"

USTRUCT(BlueprintType)
struct PROJECT_GODOFWEAPON_API FPlayerStatStructure
{
	GENERATED_USTRUCT_BODY();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrentHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ShortRangeAttackForce;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 LongRangeAttackForce;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackSpeedMultifier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MoveSpeedMultifier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackRangeMultifier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Recovery;

	FPlayerStatStructure()
		: CurrentHP(60), MaxHP(60), ShortRangeAttackForce(2), LongRangeAttackForce(2),
		AttackSpeedMultifier(1.0f), MoveSpeedMultifier(1.0f), AttackRangeMultifier(1.0f), Recovery(0)
	{
	}
};
