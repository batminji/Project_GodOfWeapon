// Fill out your copyright notice in the Description page of Project Settings.


#include "InGamePlayer.h"
#include "InputAction.h"
#include "EnhancedInputComponent.h"
#include "Kismet/KismetMathLibrary.h"

AInGamePlayer::AInGamePlayer()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AInGamePlayer::UpdatePlayerStat(const FPlayerStatStructure& InStat, const int32 InCoinCnt)
{
	PlayerStat = InStat;
	CoinCnt = InCoinCnt;
}

void AInGamePlayer::RecoverPlayerHP()
{
	PlayerStat.CurrentHP = FMath::Min(PlayerStat.CurrentHP + PlayerStat.Recovery, PlayerStat.MaxHP);
}

void AInGamePlayer::BeginPlay()
{
	Super::BeginPlay();
	
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

