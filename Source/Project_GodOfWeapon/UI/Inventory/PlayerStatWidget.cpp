// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStatWidget.h"
#include "Components/TextBlock.h"
#include "../../Player/PlayerStateBase.h"
#include "Kismet/GameplayStatics.h"

void UPlayerStatWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerState = GetOwningPlayer()->GetPlayerState<APlayerStateBase>();
}

void UPlayerStatWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UPlayerStatWidget::UpdatePlayerStat(const FPlayerStatStructure& InStat)
{
	if (!PlayerState)
	{
		return;
	}

	FString IntString = FString::Printf(TEXT("%d"), InStat.CurrentHP);
	CurrentHPText->SetText(FText::FromString(IntString));

	IntString = FString::Printf(TEXT("%d"), InStat.MaxHP);
	MaxHPText->SetText(FText::FromString(IntString));

	IntString = FString::Printf(TEXT("%d"), InStat.ShortRangeAttackForce);
	ShortAttackForceText->SetText(FText::FromString(IntString));

	IntString = FString::Printf(TEXT("%d"), InStat.LongRangeAttackForce);
	LongAttackForceText->SetText(FText::FromString(IntString));

	FString FloatString = FString::Printf(TEXT("%.1f"), InStat.AttackSpeedMultifier);
	AttackSpeedText->SetText(FText::FromString(FloatString));

	FloatString = FString::Printf(TEXT("%.1f"), InStat.MoveSpeedMultifier);
	MoveSpeedText->SetText(FText::FromString(FloatString));

	FloatString = FString::Printf(TEXT("%.1f"), InStat.AttackRangeMultifier);
	AttackRangeText->SetText(FText::FromString(FloatString));

	IntString = FString::Printf(TEXT("%d"), InStat.Recovery);
	RecoverText->SetText(FText::FromString(IntString));
}
