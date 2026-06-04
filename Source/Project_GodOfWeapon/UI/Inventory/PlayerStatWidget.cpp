// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStatWidget.h"
#include "Components/TextBlock.h"
#include "../../Player/PlayerStateBase.h"
#include "Kismet/GameplayStatics.h"
#include "../../Structs/PlayerStructs.h"

void UPlayerStatWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerState = GetOwningPlayer()->GetPlayerState<APlayerStateBase>();
}

void UPlayerStatWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	UpdatePlayerStat();
}

void UPlayerStatWidget::UpdatePlayerStat()
{
	if (!PlayerState)
	{
		return;
	}

	FPlayerStatStructure& Stat = PlayerState->PlayerStat;

	FString IntString = FString::Printf(TEXT("%d"), Stat.CurrentHP);
	CurrentHPText->SetText(FText::FromString(IntString));

	IntString = FString::Printf(TEXT("%d"), Stat.MaxHP);
	MaxHPText->SetText(FText::FromString(IntString));

	IntString = FString::Printf(TEXT("%d"), Stat.ShortRangeAttackForce);
	ShortAttackForceText->SetText(FText::FromString(IntString));

	IntString = FString::Printf(TEXT("%d"), Stat.LongRangeAttackForce);
	LongAttackForceText->SetText(FText::FromString(IntString));

	FString FloatString = FString::Printf(TEXT("%.1f"), Stat.AttackSpeedMultifier);
	AttackSpeedText->SetText(FText::FromString(FloatString));

	FloatString = FString::Printf(TEXT("%.1f"), Stat.MoveSpeedMultifier);
	MoveSpeedText->SetText(FText::FromString(FloatString));

	FloatString = FString::Printf(TEXT("%.1f"), Stat.AttackRangeMultifier);
	AttackRangeText->SetText(FText::FromString(FloatString));

	IntString = FString::Printf(TEXT("%d"), Stat.Recovery);
	RecoverText->SetText(FText::FromString(IntString));
}
