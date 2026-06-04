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
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    // Wave Stage
    UPROPERTY(ReplicatedUsing = OnReplicate_CurrentStage, BlueprintReadWrite)
    int32 CurrentStage = 1;

    UPROPERTY(Replicated, BlueprintReadWrite)
    float LevelMultiplier = 0.0f;

    UPROPERTY(Replicated, BlueprintReadWrite)
    int32 CurrentAliveMonsterCount = 0;

    // Game Over
    UPROPERTY(ReplicatedUsing = OnReplicate_bIsVictory, BlueprintReadWrite)
    bool bIsVictory = false;

    UFUNCTION()
    void OnReplicate_CurrentStage();

    UFUNCTION()
    void OnReplicate_bIsVictory();
};
