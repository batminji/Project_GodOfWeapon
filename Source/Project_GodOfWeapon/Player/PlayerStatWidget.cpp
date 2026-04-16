// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStatWidget.h"
#include "Components/TextBlock.h"
#include "Project_GodOfWeapon/GodOfWeaponGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerStatStructure.h"

void UPlayerStatWidget::NativeConstruct()
{
	Super::NativeConstruct();
	GameInstance = Cast<UGodOfWeaponGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
}

void UPlayerStatWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	if(GameInstance)
	{
		FString IntString = FString::Printf(TEXT("%d"), GameInstance->PlayerStat.CurrentHP);
		CurrentHPText->SetText(FText::FromString(IntString));

		IntString = FString::Printf(TEXT("%d"), GameInstance->PlayerStat.MaxHP);
		MaxHPText->SetText(FText::FromString(IntString));

		IntString = FString::Printf(TEXT("%d"), GameInstance->PlayerStat.ShortRangeAttackForce);
		ShortAttackForceText->SetText(FText::FromString(IntString));

		IntString = FString::Printf(TEXT("%d"), GameInstance->PlayerStat.LongRangeAttackForce);
		LongAttackForceText->SetText(FText::FromString(IntString));

		FString FloatString = FString::Printf(TEXT("%.1f"), GameInstance->PlayerStat.AttackSpeedMultifier);
		AttackSpeedText->SetText(FText::FromString(FloatString));

		FloatString = FString::Printf(TEXT("%.1f"), GameInstance->PlayerStat.MoveSpeedMultifier);
		MoveSpeedText->SetText(FText::FromString(FloatString));

		FloatString = FString::Printf(TEXT("%.1f"), GameInstance->PlayerStat.AttackRangeMultifier);
		AttackRangeText->SetText(FText::FromString(FloatString));

		IntString = FString::Printf(TEXT("%d"), GameInstance->PlayerStat.Recovery);
		RecoverText->SetText(FText::FromString(IntString));
	}
}
