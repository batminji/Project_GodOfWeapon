// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Player/PlayerStatStructure.h"
#include "Enums/StageEnums.h"
#include "Structs/PlayerStructs.h"
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

	// Player
	UFUNCTION(BlueprintCallable, Category = "Player")
	void LevelUpPlayer();

	// Coin
	UFUNCTION(BlueprintPure, Category = "Coin")
	bool HasEnoughCoin(int32 InAmount) const;

	UFUNCTION(BlueprintCallable, Category = "Coin")
	void DeductCoin(int32 InAmount);

	// Gettters
	TArray<FSavedItemData>& GetInventoryData() { return InventoryData; }

	int32 GetPlayerCoin() const { return PlayerCoin; }

	FPlayerStatStructure& GetPlayerStat() { return PlayerStat; }

protected:
	// Player Data
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Data")
	FCustomizeData PlayerCustomData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Data")
	FPlayerStatStructure PlayerStat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Data")
	int32 PlayerCoin = 30;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Data")
	int32 PlayerEarnedCoin = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Data")
	int32 TotalMonsterDefeated = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Data")
	int32 TotalDamage = 0;

	// Inventory Data
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory Data")
	TArray<FSavedItemData> InventoryData;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory Data")
	int32 InventoryColumns = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory Data")
	int32 InventoryRows = 5;

	// Stage Data
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stage Data")
	int32 CurrentStage = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stage Data")
	float LevelMultiplier = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stage Data")
	EDifficulty Difficulty = EDifficulty::Easy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stage Data")
	bool bIsVictory = false;

	// Data Table
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player Level Data Table")
	TObjectPtr<UDataTable> PlayerLevelDataTable;

private:
	void UpdatePlayerStat(float Multiplier);
	void ExpandInventory();
};
