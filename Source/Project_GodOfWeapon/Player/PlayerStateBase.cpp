// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStateBase.h"
#include "Net/UnrealNetwork.h"
#include "InGamePlayer.h"
#include "EngineUtils.h"

APlayerStateBase::APlayerStateBase()
{
}

void APlayerStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APlayerStateBase, CustomData);
	DOREPLIFETIME(APlayerStateBase, InventoryItems);
	DOREPLIFETIME(APlayerStateBase, PlayerStat);
	DOREPLIFETIME(APlayerStateBase, PlayerCoin);
}

void APlayerStateBase::CopyProperties(APlayerState* PlayerState)
{
	Super::CopyProperties(PlayerState);

	APlayerStateBase* NewPlayerState = Cast<APlayerStateBase>(PlayerState);
	if (NewPlayerState)
	{
		NewPlayerState->PlayerCoin = this->PlayerCoin;
		NewPlayerState->PlayerStat = this->PlayerStat;
		NewPlayerState->PlayerEarnedCoin = this->PlayerEarnedCoin;
		NewPlayerState->TotalMonsterDefeated = this->TotalMonsterDefeated;
		NewPlayerState->TotalDamage = this->TotalDamage;
		NewPlayerState->InventoryItems = this->InventoryItems;
	}
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

void APlayerStateBase::OnRep_CustomData()
{
	AInGamePlayer* TargetPlayer = Cast<AInGamePlayer>(GetPawn());

	if (!TargetPlayer)
	{
		for (AInGamePlayer* TempPlayer : TActorRange<AInGamePlayer>(GetWorld()))
		{
			if (TempPlayer && TempPlayer->GetPlayerState() == this)
			{
				TargetPlayer = TempPlayer;
				break;
			}
		}
	}

	if (TargetPlayer)
	{
		TargetPlayer->UpdatePlayerCustom(CustomData);
	}
}

void APlayerStateBase::OnRep_PlayerStat()
{
	AInGamePlayer* TargetPlayer = Cast<AInGamePlayer>(GetPawn());
	if (!TargetPlayer)
	{
		for (AInGamePlayer* TempPlayer : TActorRange<AInGamePlayer>(GetWorld()))
		{
			if (TempPlayer && TempPlayer->GetPlayerState() == this)
			{
				TargetPlayer = TempPlayer;
				break;
			}
		}
	}
	if (TargetPlayer)
	{
		TargetPlayer->SetCurrentPlayerStat(PlayerStat);
	}
}

void APlayerStateBase::OnRep_InventoryItems()
{
	AInGamePlayer* TargetPlayer = Cast<AInGamePlayer>(GetPawn());

	if (!TargetPlayer)
	{
		for (AInGamePlayer* TempPlayer : TActorRange<AInGamePlayer>(GetWorld()))
		{
			if (TempPlayer && TempPlayer->GetPlayerState() == this)
			{
				TargetPlayer = TempPlayer;
				break;
			}
		}
	}

	if (TargetPlayer)
	{
		TargetPlayer->ApplyInventoryItems(InventoryItems);
	}
}

void APlayerStateBase::Server_UpdateStat(FPlayerStatStructure InPlayerStat)
{
	if (HasAuthority())
	{
		PlayerStat = InPlayerStat;
		OnRep_PlayerStat();
	}
}

void APlayerStateBase::Server_UpdateCoin(int32 InCoin)
{
	if (HasAuthority())
	{
		PlayerCoin = InCoin;
	}
}
