// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryGameMode.h"
#include "InventoryGameStateBase.h"
#include "../Controller/InventoryController.h"

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
					
					ShowLoadingScreen();

					GetWorld()->GetTimerManager().SetTimer(TravelTimerHandle, this, &AInventoryGameMode::ExecuteServerTravel, 0.2f, false);
				}
				InventoryGameState->SetLeftTime(InventoryGameState->GetLeftTime() - 1);
			}
		},
		1.0f,
		true
	);
}

void AInventoryGameMode::ShowLoadingScreen()
{
	if (!HasAuthority())
	{
		return;
	}

	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		AInventoryController* PlayerController = Cast<AInventoryController>(*It);
		if (PlayerController)
		{
			PlayerController->S2C_ShowLoadingScreen();
		}
	}
}

void AInventoryGameMode::ExecuteServerTravel()
{
	GetWorld()->GetTimerManager().ClearTimer(TravelTimerHandle);

	GetWorld()->ServerTravel("/Game/Maps/InGameMap?listen");
}
