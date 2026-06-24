// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "InGameStateBase.generated.h"

UCLASS()
class PROJECT_GODOFWEAPON_API AInGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	
public:
    AInGameStateBase();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Timer")
	float GetLeftTime() const { return LeftTime; }

public:
    // Wave Stage
    UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite)
    float LeftTime = 0.0f;

    UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite)
    int32 CurrentStage = 1;

    UPROPERTY(Replicated, BlueprintReadWrite)
    float LevelMultiplier = 0.0f;

    UPROPERTY(Replicated, BlueprintReadWrite)
    int32 CurrentAliveMonsterCount = 0;
};
