// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MonsterAIController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_GODOFWEAPON_API AMonsterAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "AI")
	void RunAI();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "AI")
	void StopAI();
};
