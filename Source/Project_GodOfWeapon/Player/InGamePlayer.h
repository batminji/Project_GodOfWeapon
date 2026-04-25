// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Structs/PlayerStructs.h"
#include "InGamePlayer.generated.h"

UCLASS()
class PROJECT_GODOFWEAPON_API AInGamePlayer : public ACharacter
{
	GENERATED_BODY()

public:
	AInGamePlayer();

	void UpdatePlayerStat(const FPlayerStatStructure& InStat, const int32 InCoinCnt);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void UpdatePlayerCustom(const FCustomData& InCustomData); // For Data Table Load

protected:
	virtual void BeginPlay() override;

	FPlayerStatStructure PlayerStat{};

	int32 CoinCnt{0};

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
