// Fill out your copyright notice in the Description page of Project Settings.


#include "InGamePlayer.h"

// Sets default values
AInGamePlayer::AInGamePlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AInGamePlayer::UpdatePlayerStat(const FPlayerStatStructure& InStat, const int32 InCoinCnt)
{
	PlayerStat = InStat;
	CoinCnt = InCoinCnt;
}

// Called when the game starts or when spawned
void AInGamePlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInGamePlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AInGamePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

