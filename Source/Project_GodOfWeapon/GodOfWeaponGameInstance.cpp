// Fill out your copyright notice in the Description page of Project Settings.


#include "GodOfWeaponGameInstance.h"
#include "Engine/DataTable.h"


UGodOfWeaponGameInstance::UGodOfWeaponGameInstance()
{

}

void UGodOfWeaponGameInstance::LevelUpPlayer()
{
	if (!PlayerLevelDataTable) return;

	FName RowName = FName(*FString::FromInt(CurrentStage));
	FPlayerLevel* Row = PlayerLevelDataTable->FindRow<FPlayerLevel>(RowName, TEXT("LevelUpPlayer"));

	if (Row)
	{
		UpdatePlayerStat(Row->Multiplier);
		ExpandInventory();
	}
}

void UGodOfWeaponGameInstance::UpdatePlayerCustomData(const FCustomData& InCustomData)
{
	PlayerCustomData = InCustomData;
}

void UGodOfWeaponGameInstance::UpdateStageClear(const FPlayerStatStructure& InPlayerStat, const int32& InPlayerCoin, const int32& InPlayerEarnedCoin, const int32& InTotalDamage, const int32& InTotalMonsterDefeated)
{
	PlayerStat = InPlayerStat;
	PlayerCoin = InPlayerCoin;
	PlayerEarnedCoin += InPlayerEarnedCoin;
	TotalDamage += InTotalDamage;
	TotalMonsterDefeated += InTotalMonsterDefeated;
}

bool UGodOfWeaponGameInstance::HasEnoughCoin(const int32& InAmount) const
{
	return PlayerCoin >= InAmount;
}

void UGodOfWeaponGameInstance::DeductCoin(const int32& InAmount)
{
	if (HasEnoughCoin(InAmount))
	{
		PlayerCoin -= InAmount;
	}
}

void UGodOfWeaponGameInstance::UpdatePlayerStat(float Multiplier)
{
	PlayerStat.CurrentHP = static_cast<int32>(PlayerStat.MaxHP * Multiplier);
	PlayerStat.MaxHP = static_cast<int32>(PlayerStat.MaxHP * Multiplier);
	PlayerStat.ShortRangeAttackForce = static_cast<int32>(PlayerStat.ShortRangeAttackForce * Multiplier);
	PlayerStat.LongRangeAttackForce = static_cast<int32>(PlayerStat.LongRangeAttackForce * Multiplier);
	PlayerStat.AttackRangeMultifier = PlayerStat.AttackRangeMultifier * Multiplier;
	PlayerStat.AttackSpeedMultifier = PlayerStat.AttackSpeedMultifier * Multiplier;
	PlayerStat.MoveSpeedMultifier = PlayerStat.MoveSpeedMultifier * Multiplier;
	PlayerStat.Recovery = static_cast<int32>(PlayerStat.Recovery * Multiplier);
}

void UGodOfWeaponGameInstance::ExpandInventory()
{
	bool bRandom = FMath::RandBool();
	int32& Selected = bRandom ? InventoryColumns : InventoryRows;
	Selected++;
}
