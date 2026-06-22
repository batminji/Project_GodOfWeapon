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

					SavedPlayers.Empty();

					for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
					{
						AInventoryController* PlayerController = Cast<AInventoryController>(*It);
						if (PlayerController)
						{
							PlayerController->S2C_UpdatePlayerInventory();
						}
					}
				}
				UE_LOG(LogTemp, Log, TEXT("Left Time: %d"), InventoryGameState->GetLeftTime());
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
	GetWorld()->ServerTravel("/Game/Maps/InGameMap?listen");
}

void AInventoryGameMode::OnPlayerSaveCompleted(AInventoryController* PlayerController)
{
	if (!PlayerController || SavedPlayers.Contains(PlayerController))
	{
		return;
	}

	SavedPlayers.Add(PlayerController);

	if (SavedPlayers.Num() >= GetNumPlayers())
	{
		ExecuteServerTravel();
	}
}
