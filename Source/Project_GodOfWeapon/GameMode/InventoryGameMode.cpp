// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryGameMode.h"
#include "InventoryGameStateBase.h"

void AInventoryGameMode::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(
		LeftTimerHandle,
		[&]()
		{
			AInventoryGameStateBase* InventoryGameState = GetGameState<AInventoryGameStateBase>();
			if (InventoryGameState)
			{
				if (InventoryGameState->GetLeftTime() <= 0)
				{
					GetWorld()->GetTimerManager().ClearTimer(LeftTimerHandle);
					// StartGame();
				}
				InventoryGameState->SetLeftTime(InventoryGameState->GetLeftTime() - 1);
			}
		},
		1.0f,
		true
	);
}
