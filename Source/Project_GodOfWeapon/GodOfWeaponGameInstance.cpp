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

bool UGodOfWeaponGameInstance::HasEnoughCoin(int32 InAmount) const
{
	return PlayerCoin >= InAmount;
}

void UGodOfWeaponGameInstance::DeductCoin(int32 InAmount)
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
