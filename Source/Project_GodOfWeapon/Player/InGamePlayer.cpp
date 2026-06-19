// Fill out your copyright notice in the Description page of Project Settings.


#include "InGamePlayer.h"
#include "InputAction.h"
#include "EnhancedInputComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "PlayerStateBase.h"
#include "../GodOfWeaponGameInstance.h"

AInGamePlayer::AInGamePlayer()
{
	PrimaryActorTick.bCanEverTick = true;

}

bool AInGamePlayer::C2S_SendCustomData_Validate(const FCustomData& InCustomData)
{
	return true;
}

void AInGamePlayer::C2S_SendCustomData_Implementation(const FCustomData& InCustomData)
{
	APlayerStateBase* MyPlayerState = GetPlayerState<APlayerStateBase>();
	if (MyPlayerState)
	{
		MyPlayerState->CustomData = InCustomData;
		UpdatePlayerCustom(InCustomData);
	}
}

bool AInGamePlayer::C2S_SendInventory_Validate(const TArray<FSavedItemData>& InItems)
{
	return true;
}

void AInGamePlayer::C2S_SendInventory_Implementation(const TArray<FSavedItemData>& InItems)
{
	APlayerStateBase* MyPlayerState = GetPlayerState<APlayerStateBase>();
	if (MyPlayerState)
	{
		MyPlayerState->InventoryItems = InItems;
		ApplyInventoryItems(InItems);
	}
}

void AInGamePlayer::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	TryApplyCustomData();
	TryApplyInventoryItems();
}

void AInGamePlayer::RecoverPlayerHP()
{
	APlayerStateBase* MyPlayerState = GetPlayerState<APlayerStateBase>();
	if (MyPlayerState)
	{
		FPlayerStatStructure Stat = MyPlayerState->GetPlayerStat();
		Stat.CurrentHP = FMath::Min(Stat.CurrentHP + Stat.Recovery, Stat.MaxHP);
		MyPlayerState->SetCurrentHP(Stat.CurrentHP);
	}
}

FPlayerStatStructure AInGamePlayer::GetCurrentPlayerStat() const
{
	APlayerStateBase* MyPlayerState = GetPlayerState<APlayerStateBase>();

	if(!MyPlayerState)
	{
		return FPlayerStatStructure{};
	}
	return MyPlayerState->GetPlayerStat();
}

int32 AInGamePlayer::GetCoinCnt() const
{
	APlayerStateBase* MyPlayerState = GetPlayerState<APlayerStateBase>();

	if(!MyPlayerState)
	{
		return 0;
	}
	return MyPlayerState->GetPlayerCoin();
}

void AInGamePlayer::ClientExpandInventory_Implementation()
{
	UGodOfWeaponGameInstance* GameInstance = Cast<UGodOfWeaponGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		GameInstance->ExpandInventory();
	}
}

void AInGamePlayer::SetCurrentPlayerStat(const FPlayerStatStructure& InCurrentPlayerStat)
{
	APlayerStateBase* MyPlayerState = GetPlayerState<APlayerStateBase>();
	if(MyPlayerState)
	{
		MyPlayerState->PlayerStat = InCurrentPlayerStat;
	}
}

void AInGamePlayer::SetCoinCnt(int32 InCoinCnt)
{
	APlayerStateBase* MyPlayerState = GetPlayerState<APlayerStateBase>();
	if(MyPlayerState)
	{
		MyPlayerState->PlayerCoin = InCoinCnt;
	}
}

void AInGamePlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

void AInGamePlayer::PawnClientRestart()
{
	Super::PawnClientRestart();

	UGodOfWeaponGameInstance* GameInstance = Cast<UGodOfWeaponGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		C2S_SendCustomData(GameInstance->GetPlayerCustomData());
		C2S_SendInventory(GameInstance->GetInventoryData());
	}
}

void AInGamePlayer::TryApplyCustomData()
{
	APlayerStateBase* MyPlayerState = GetPlayerState<APlayerStateBase>();
	if (MyPlayerState)
	{
		UpdatePlayerCustom(MyPlayerState->CustomData);
	}
}

void AInGamePlayer::TryApplyInventoryItems()
{
	APlayerStateBase* MyPlayerState = GetPlayerState<APlayerStateBase>();
	if (MyPlayerState)
	{
		ApplyInventoryItems(MyPlayerState->InventoryItems);
	}
}

void AInGamePlayer::Move(const FInputActionValue& InValue)
{
	FVector2D MoveDirection = InValue.Get<FVector2D>();

	FRotator ControlRotation = FRotator(0.0f, GetControlRotation().Yaw, 0.0f);
	FVector ForwardVector = UKismetMathLibrary::GetForwardVector(ControlRotation);
	FVector RightVector = UKismetMathLibrary::GetRightVector(ControlRotation);

	AddMovementInput(ForwardVector * MoveDirection.X);
	AddMovementInput(RightVector * MoveDirection.Y);
}

void AInGamePlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInGamePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EIC)
	{
		EIC->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AInGamePlayer::Move);
		EIC->BindAction(IA_Jump, ETriggerEvent::Triggered, this, &AInGamePlayer::Jump);
		EIC->BindAction(IA_Jump, ETriggerEvent::Completed, this, &AInGamePlayer::StopJumping);
		EIC->BindAction(IA_Jump, ETriggerEvent::Canceled, this, &AInGamePlayer::StopJumping);
	}
}

