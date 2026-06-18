// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "InventoryGameStateBase.generated.h"

UCLASS()
class PROJECT_GODOFWEAPON_API AInventoryGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void BeginPlay() override;

	void Init();

	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Time")
	int32 GetLeftTime() const { return LeftTime; }

	void SetLeftTime(int32 NewLeftTime) { LeftTime = NewLeftTime; }
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated)
	int32 LeftTime = 30;
};
