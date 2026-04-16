// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Player/PlayerStatStructure.h"
#include "GodOfWeaponGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_GODOFWEAPON_API UGodOfWeaponGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UGodOfWeaponGameInstance();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Economy")
	int32 PlayerMoney = 30;

	UFUNCTION(BlueprintPure, Category = "Economy")
	bool HasEnoughMoney(int32 InAmount) const;

	UFUNCTION(BlueprintCallable, Category = "Economy")
	void DeductMoney(int32 InAmount);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stat")
	FPlayerStatStructure PlayerStat;
};
