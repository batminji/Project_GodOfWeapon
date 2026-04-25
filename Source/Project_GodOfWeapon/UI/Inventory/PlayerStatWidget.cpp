// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStatWidget.h"
#include "Components/TextBlock.h"
#include "../../GodOfWeaponGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "../../Structs/PlayerStructs.h"

void UPlayerStatWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GameInstance = Cast<UGodOfWeaponGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
}

void UPlayerStatWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	UpdatePlayerStat();
}

void UPlayerStatWidget::UpdatePlayerStat()
{
	if (GameInstance)
	{
		FString IntString = FString::Printf(TEXT("%d"), GameInstance->GetPlayerStat().CurrentHP);
		CurrentHPText->SetText(FText::FromString(IntString));

		IntString = FString::Printf(TEXT("%d"), GameInstance->GetPlayerStat().MaxHP);
		MaxHPText->SetText(FText::FromString(IntString));

		IntString = FString::Printf(TEXT("%d"), GameInstance->GetPlayerStat().ShortRangeAttackForce);
		ShortAttackForceText->SetText(FText::FromString(IntString));

		IntString = FString::Printf(TEXT("%d"), GameInstance->GetPlayerStat().LongRangeAttackForce);
		LongAttackForceText->SetText(FText::FromString(IntString));

		FString FloatString = FString::Printf(TEXT("%.1f"), GameInstance->GetPlayerStat().AttackSpeedMultifier);
		AttackSpeedText->SetText(FText::FromString(FloatString));

		FloatString = FString::Printf(TEXT("%.1f"), GameInstance->GetPlayerStat().MoveSpeedMultifier);
		MoveSpeedText->SetText(FText::FromString(FloatString));

		FloatString = FString::Printf(TEXT("%.1f"), GameInstance->GetPlayerStat().AttackRangeMultifier);
		AttackRangeText->SetText(FText::FromString(FloatString));

		IntString = FString::Printf(TEXT("%d"), GameInstance->GetPlayerStat().Recovery);
		RecoverText->SetText(FText::FromString(IntString));
	}
}
