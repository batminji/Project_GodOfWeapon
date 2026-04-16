// Fill out your copyright notice in the Description page of Project Settings.


#include "GodOfWeaponGameInstance.h"

UGodOfWeaponGameInstance::UGodOfWeaponGameInstance()
{
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
