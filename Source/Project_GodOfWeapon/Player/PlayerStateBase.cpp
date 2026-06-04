// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStateBase.h"
#include "Net/UnrealNetwork.h"

APlayerStateBase::APlayerStateBase()
{
}

void APlayerStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APlayerStateBase, CustomData);
	DOREPLIFETIME(APlayerStateBase, PlayerStat);
	DOREPLIFETIME(APlayerStateBase, PlayerCoin);
	DOREPLIFETIME(APlayerStateBase, PlayerEarnedCoin);
	DOREPLIFETIME(APlayerStateBase, TotalMonsterDefeated);
	DOREPLIFETIME(APlayerStateBase, TotalDamage);
}

void APlayerStateBase::AddCoin(int32 InAmount)
{
	if (!HasAuthority())
	{
		return;
	}
	PlayerCoin += InAmount;
}

void APlayerStateBase::DeductCoin(int32 InAmount)
{
	if (!HasAuthority())
	{
		return;
	}
	if (HasEnoughCoin(InAmount))
	{
		PlayerCoin -= InAmount;
	}
}

void APlayerStateBase::ApplyStatMultiplier(float Multiplier)
{
	if (!HasAuthority())
	{
		return;
	}

	PlayerStat.CurrentHP = static_cast<int32>(PlayerStat.MaxHP * Multiplier);
	PlayerStat.MaxHP = static_cast<int32>(PlayerStat.MaxHP * Multiplier);
	PlayerStat.ShortRangeAttackForce = static_cast<int32>(PlayerStat.ShortRangeAttackForce * Multiplier);
	PlayerStat.LongRangeAttackForce = static_cast<int32>(PlayerStat.LongRangeAttackForce * Multiplier);
	PlayerStat.AttackRangeMultifier *= Multiplier;
	PlayerStat.AttackSpeedMultifier *= Multiplier;
	PlayerStat.MoveSpeedMultifier *= Multiplier;
	PlayerStat.Recovery = static_cast<int32>(PlayerStat.Recovery * Multiplier);
}

void APlayerStateBase::OnReplicate_CustomData()
{
}

void APlayerStateBase::OnReplicate_PlayerCoin()
{
}
