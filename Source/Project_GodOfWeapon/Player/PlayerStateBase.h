// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "../Structs/PlayerStructs.h"
#include "../Structs/ItemStructs.h"
#include "PlayerStateBase.generated.h"

UCLASS()
class PROJECT_GODOFWEAPON_API APlayerStateBase : public APlayerState
{
	GENERATED_BODY()
	
public:
	APlayerStateBase();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintPure)
	bool HasEnoughCoin(int32 InAmount) const { return PlayerCoin >= InAmount; }

	UFUNCTION(BlueprintCallable)
	void AddCoin(int32 InAmount);

	UFUNCTION(BlueprintCallable)
	void DeductCoin(int32 InAmount);

	// Player Stat Update - Server Only
	void ApplyStatMultiplier(float Multiplier);

	// Getters
	int32 GetPlayerCoin() const { return PlayerCoin; }
	FPlayerStatStructure& GetPlayerStat() { return PlayerStat; }
	FCustomData& GetCustomData() { return CustomData; }

	// Replication
	UPROPERTY(ReplicatedUsing = OnReplicate_CustomData, BlueprintReadWrite)
	FCustomData CustomData;

	UPROPERTY(Replicated, BlueprintReadWrite)
	FPlayerStatStructure PlayerStat;

	UPROPERTY(ReplicatedUsing = OnReplicate_PlayerCoin, BlueprintReadWrite)
	int32 PlayerCoin = 30;

	UPROPERTY(Replicated, BlueprintReadWrite)
	int32 PlayerEarnedCoin = 0;

	UPROPERTY(Replicated, BlueprintReadWrite)
	int32 TotalMonsterDefeated = 0;

	UPROPERTY(Replicated, BlueprintReadWrite)
	int32 TotalDamage = 0;

	UPROPERTY(ReplicatedUsing = OnReplicate_InventoryItems, BlueprintReadWrite)
	TArray<FSavedItemData> InventoryItems;

	UFUNCTION()
	void OnReplicate_CustomData();

	UFUNCTION()
	void OnReplicate_PlayerCoin();

	UFUNCTION()
	void OnReplicate_InventoryItems();
};
