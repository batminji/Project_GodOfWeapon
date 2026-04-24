// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Player/PlayerStatStructure.h"
#include "Enums/StageEnums.h"
#include "GodOfWeaponGameInstance.generated.h"

USTRUCT(BlueprintType)
struct FSavedItemData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemRowName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FIntPoint TopLeftTile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsRotated;
};

UCLASS()
class PROJECT_GODOFWEAPON_API UGodOfWeaponGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UGodOfWeaponGameInstance();

	UFUNCTION(BlueprintPure, Category = "Coin")
	bool HasEnoughCoin(int32 InAmount) const;

	UFUNCTION(BlueprintCallable, Category = "Coin")
	void DeductCoin(int32 InAmount);

	TArray<FSavedItemData>& GetInventoryData() { return InventoryData; }

	int32 GetPlayerCoin() const { return PlayerCoin; }

	FPlayerStatStructure& GetPlayerStat() { return PlayerStat; }

protected:
	// Player Date
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Data")
	FPlayerStatStructure PlayerStat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Data")
	int32 PlayerCoin = 30;

	// Inventory Data
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory Data")
	TArray<FSavedItemData> InventoryData;

	// Stage Data
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stage Data")
	int32 CurrentStage = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stage Data")
	float LevelMultiplier = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stage Data")
	EDifficulty Difficulty = EDifficulty::Easy;
};
