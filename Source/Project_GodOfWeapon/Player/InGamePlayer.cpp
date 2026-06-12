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

void AInGamePlayer::UpdatePlayerStat(const FPlayerStatStructure& InStat, const int32 InCoinCnt)
{
	PlayerStat = InStat;
	CoinCnt = InCoinCnt;
}

void AInGamePlayer::ServerSendCustomData_Implementation(const FCustomData& InCustomData)
{
	APlayerStateBase* MyPlayerState = GetPlayerState<APlayerStateBase>();
	if (MyPlayerState)
	{
		MyPlayerState->CustomData = InCustomData;
		UpdatePlayerCustom(InCustomData);
	}
}

void AInGamePlayer::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	
	TryApplyCustomData();
}

void AInGamePlayer::RecoverPlayerHP()
{
	PlayerStat.CurrentHP = FMath::Min(PlayerStat.CurrentHP + PlayerStat.Recovery, PlayerStat.MaxHP);
}

void AInGamePlayer::ClientExpandInventory_Implementation()
{
	UGodOfWeaponGameInstance* GameInstance = Cast<UGodOfWeaponGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		GameInstance->ExpandInventory();
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
		ServerSendCustomData(GameInstance->GetPlayerCustomData());
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

