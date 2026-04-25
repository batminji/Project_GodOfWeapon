// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Enums/StageEnums.h"
#include "Structs/PlayerStructs.h"
#include "Structs/ItemStructs.h"
#include "GodOfWeaponGameInstance.generated.h"

UCLASS()
class PROJECT_GODOFWEAPON_API UGodOfWeaponGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UGodOfWeaponGameInstance();

	// Player
	UFUNCTION(BlueprintCallable, Category = "Player")
	void LevelUpPlayer();

	UFUNCTION(BlueprintCallable, Category = "Player")
	void UpdatePlayerCustomData(const FCustomData& InCustomData);

	// Stage
	UFUNCTION(BlueprintCallable, Category = "Stage")
	void UpdateStageClear(const FPlayerStatStructure& InPlayerStat, const int32& InPlayerCoin, const int32& InPlayerEarnedCoin, const int32& InTotalDamage, const int32& InTotalMonsterDefeated);

	// Coin
	UFUNCTION(BlueprintPure, Category = "Coin")
	bool HasEnoughCoin(const int32& InAmount) const;

	UFUNCTION(BlueprintCallable, Category = "Coin")
	void DeductCoin(const int32& InAmount);

	// Gettters
	TArray<FSavedItemData>& GetInventoryData() { return InventoryData; }

	int32 GetPlayerCoin() const { return PlayerCoin; }

	FPlayerStatStructure& GetPlayerStat() { return PlayerStat; }

	FCustomData& GetPlayerCustomData() { return PlayerCustomData; }

	int32 GetCurrentStage() const { return CurrentStage; }

	float GetLevelMultiplier() const { return LevelMultiplier; }

	// Setters
	void SetDifficulty(const EDifficulty InDifficulty) { Difficulty = InDifficulty; }

	void SetLevelMultiplier(const float InMultiplier) { LevelMultiplier = InMultiplier; }

protected:
	// Player Data
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Data")
	FCustomData PlayerCustomData;

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
