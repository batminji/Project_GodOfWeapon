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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	int32 PlayerCoin = 30;

	UFUNCTION(BlueprintPure, Category = "Coin")
	bool HasEnoughCoin(int32 InAmount) const;

	UFUNCTION(BlueprintCallable, Category = "Coin")
	void DeductCoin(int32 InAmount);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	FPlayerStatStructure PlayerStat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TArray<FSavedItemData> InventoryData;
};
