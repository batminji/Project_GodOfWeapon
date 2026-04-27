// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Structs/PlayerStructs.h"
#include "InputActionValue.h"
#include "InGamePlayer.generated.h"

class UInputAction;

UCLASS()
class PROJECT_GODOFWEAPON_API AInGamePlayer : public ACharacter
{
	GENERATED_BODY()

public:
	AInGamePlayer();

	void UpdatePlayerStat(const FPlayerStatStructure& InStat, const int32 InCoinCnt);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void UpdatePlayerCustom(const FCustomData& InCustomData); // For Data Table Load

	UFUNCTION(BlueprintCallable, Category = "HP")
	void RecoverPlayerHP();

	// Getters
	FPlayerStatStructure& GetPlayerStat() { return PlayerStat; }

	int32 GetCoinCnt() const { return CoinCnt; }

	int32 GetEarnedCoinCnt() const { return EarnedCoinCnt; }

	FPlayerStatStructure GetCurrentPlayerStat() const { return PlayerStat; }

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	FPlayerStatStructure PlayerStat{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	int32 CoinCnt{0};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	int32 EarnedCoinCnt{ 0 };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	bool bIsDead{ false };

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_Move;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_Jump;

	void Move(const FInputActionValue& InValue);

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
