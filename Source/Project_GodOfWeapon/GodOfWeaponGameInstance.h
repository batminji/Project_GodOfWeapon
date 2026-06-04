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

	// Setters
	void SetDifficulty(const EDifficulty InDifficulty) { Difficulty = InDifficulty; }

	void SetLevelMultiplier(const float InMultiplier) { LevelMultiplier = InMultiplier; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stage Data")
	float LevelMultiplier = 0.0f;

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

private:
	void ExpandInventory();
};
