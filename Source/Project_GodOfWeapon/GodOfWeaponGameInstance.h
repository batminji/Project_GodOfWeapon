// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Player/PlayerStatStructure.h"
#include "GodOfWeaponGameInstance.generated.h"

USTRUCT(BlueprintType)
struct FSavedItemData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FName ItemRowName;

	UPROPERTY(BlueprintReadWrite)
	int32 TopLeftIndex;

	UPROPERTY(BlueprintReadWrite)
	bool bIsRotated;
};

UCLASS()
class PROJECT_GODOFWEAPON_API UGodOfWeaponGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UGodOfWeaponGameInstance();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Economy")
	int32 PlayerCoin = 30;

	UFUNCTION(BlueprintPure, Category = "Economy")
	bool HasEnoughCoin(int32 InAmount) const;

	UFUNCTION(BlueprintCallable, Category = "Economy")
	void DeductCoin(int32 InAmount);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stat")
	FPlayerStatStructure PlayerStat;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory Data")
	TArray<FSavedItemData> InventoryData;
};
