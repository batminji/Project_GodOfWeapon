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

	virtual void CopyProperties(APlayerState* PlayerState) override;

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
	FPlayerStatStructure GetPlayerStat() const { return PlayerStat; }
	FCustomData& GetCustomData() { return CustomData; }

	// Setters
	void SetCurrentHP(int32 InCurrentHP) { PlayerStat.CurrentHP = InCurrentHP; }
	void SetRecovery(int32 InRecovery) { PlayerStat.Recovery = InRecovery; }
	void SetMoveSpeedMultiplier(float InMoveSpeedMultiplier) { PlayerStat.MoveSpeedMultifier = InMoveSpeedMultiplier; }
	void SetShortRangeAttackForce(int32 InShortRangeAttackForce) { PlayerStat.ShortRangeAttackForce = InShortRangeAttackForce; }
	void SetLongRangeAttackForce(int32 InLongRangeAttackForce) { PlayerStat.LongRangeAttackForce = InLongRangeAttackForce; }

	UFUNCTION()
	void OnRep_CustomData();

	UFUNCTION()
	void OnRep_PlayerStat();

	UFUNCTION()
	void OnRep_InventoryItems();

	void Server_UpdateStat(FPlayerStatStructure InPlayerStat);

	void Server_UpdateCoin(int32 InCoin);

public:
	// Replication
	UPROPERTY(ReplicatedUsing = OnRep_CustomData, BlueprintReadWrite)
	FCustomData CustomData;

	UPROPERTY(ReplicatedUsing = OnRep_PlayerStat, BlueprintReadWrite)
	FPlayerStatStructure PlayerStat;

	UPROPERTY(BlueprintReadWrite, Replicated)
	int32 PlayerCoin = 30;

	UPROPERTY(BlueprintReadWrite)
	int32 PlayerEarnedCoin = 0;

	UPROPERTY(BlueprintReadWrite)
	int32 TotalMonsterDefeated = 0;

	UPROPERTY(BlueprintReadWrite)
	int32 TotalDamage = 0;

	UPROPERTY(ReplicatedUsing = OnRep_InventoryItems, BlueprintReadWrite)
	TArray<FSavedItemData> InventoryItems;
};
