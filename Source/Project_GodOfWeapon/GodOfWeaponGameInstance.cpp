// Fill out your copyright notice in the Description page of Project Settings.


#include "GodOfWeaponGameInstance.h"
#include "Engine/DataTable.h"


UGodOfWeaponGameInstance::UGodOfWeaponGameInstance()
{

}

void UGodOfWeaponGameInstance::UpdatePlayerCustomData(const FCustomData& InCustomData)
{
	PlayerCustomData = InCustomData;
}

void UGodOfWeaponGameInstance::ExpandInventory()
{
	bool bRandom = FMath::RandBool();
	int32& Selected = bRandom ? InventoryColumns : InventoryRows;
	Selected++;
}
