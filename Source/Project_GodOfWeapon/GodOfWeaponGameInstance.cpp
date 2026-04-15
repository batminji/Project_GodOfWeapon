// Fill out your copyright notice in the Description page of Project Settings.


#include "GodOfWeaponGameInstance.h"

UGodOfWeaponGameInstance::UGodOfWeaponGameInstance()
{
}

bool UGodOfWeaponGameInstance::HasEnoughMoney(int32 InAmount) const
{
	return PlayerMoney >= InAmount;
}

void UGodOfWeaponGameInstance::DeductMoney(int32 InAmount)
{
	if (HasEnoughMoney(InAmount))
	{
		PlayerMoney -= InAmount;
	}
}
