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

	UFUNCTION(BlueprintCallable, Category = "Player")
	void UpdatePlayerCustomData(const FCustomData& InCustomData);

	// Gettters
	TArray<FSavedItemData>& GetInventoryData() { return InventoryData; }

	FCustomData& GetPlayerCustomData() { return PlayerCustomData; }

	int32 GetInventoryColumns() const { return InventoryColumns; }

	int32 GetInventoryRows() const { return InventoryRows; }

	EDifficulty GetDifficulty() const { return Difficulty; }

	UDataTable* GetPlayerLevelDataTable() const { return PlayerLevelDataTable; }

	float GetLevelMultiplier() const { return LevelMultiplier; }

	bool GetIsVictory() const { return bIsVictory; }

	// Setters
	void SetDifficulty(const EDifficulty InDifficulty) { Difficulty = InDifficulty; }

	void SetLevelMultiplier(const float InMultiplier) { LevelMultiplier = InMultiplier; }

	void SetIsVictory(const bool bInIsVictory) { bIsVictory = bInIsVictory; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stage Data")
	float LevelMultiplier = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stage Data")
	bool bIsVictory = false;

	// Player Data
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Data")
	FCustomData PlayerCustomData;

	// Inventory Data
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory Data")
	TArray<FSavedItemData> InventoryData;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory Data")
	int32 InventoryColumns = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory Data")
	int32 InventoryRows = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stage Data")
	EDifficulty Difficulty = EDifficulty::Easy;

	// Data Table
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player Level Data Table")
	TObjectPtr<UDataTable> PlayerLevelDataTable;

public:
	// Result
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Result Data")
	int32 ResultStage = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Result Data")
	int32 ResultEarnedCoin = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Result Data")
	int32 ResultTotalDamage = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Result Data")
	int32 ResultTotalMonsterDefeated = 0;

public:
	void ExpandInventory();
};
