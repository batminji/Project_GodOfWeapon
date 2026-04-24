// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerStatWidget.generated.h"

class UTextBlock;
class UGodOfWeaponGameInstance;

UCLASS()
class PROJECT_GODOFWEAPON_API UPlayerStatWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> CurrentHPText;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> MaxHPText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ShortAttackForceText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> LongAttackForceText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> AttackSpeedText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> MoveSpeedText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> AttackRangeText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> RecoverText;

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void UpdatePlayerStat();

	TObjectPtr<UGodOfWeaponGameInstance> GameInstance;
};
