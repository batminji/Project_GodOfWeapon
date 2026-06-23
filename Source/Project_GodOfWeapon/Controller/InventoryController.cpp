// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryController.h"
#include "Blueprint/UserWidget.h"
#include "../Components/InventoryComponent.h"
#include "../UI/Inventory/InventoryWidget.h"
#include "../UI/Item/ItemWidget.h"
#include "../UI/LoadingUserWidget.h"
#include "../Player/PlayerStateBase.h"
#include "../GameMode/InventoryGameMode.h"
#include "../GodOfWeaponGameInstance.h"

AInventoryController::AInventoryController()
{
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));
}

void AInventoryController::C2S_RequestNextStage_Implementation()
{
	GetWorld()->ServerTravel("/Game/Maps/InGameMap?listen");
}

bool AInventoryController::C2S_RequestNextStage_Validate()
{
	return true;
}

void AInventoryController::S2C_ShowLoadingScreen_Implementation()
{
	if (!IsLocalController())
	{
		return;
	}

	if (LoadingScreenWidgetClass)
	{
		ULoadingUserWidget* LoadingScreen = CreateWidget<ULoadingUserWidget>(this, LoadingScreenWidgetClass);
		if (LoadingScreen)
		{
			LoadingScreen->AddToViewport();
		}
	}
}

void AInventoryController::S2C_UpdatePlayerInventory_Implementation()
{
	if(!IsLocalController())
	{
		return;
	}

	InventoryComponent->SaveInventoryToGameInstance();

	C2S_NotifySaveFinished();
}

void AInventoryController::C2S_NotifySaveFinished_Implementation()
{
	if (HasAuthority())
	{
		AInventoryGameMode* GameMode = Cast<AInventoryGameMode>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->OnPlayerSaveCompleted(this);
		}
	}
}

bool AInventoryController::C2S_NotifySaveFinished_Validate()
{
	return true;
}

void AInventoryController::C2S_RequestLoadPlayerState_Implementation(FPlayerStatStructure InPlayerStat, int32 InPlayerCoin)
{
	APlayerStateBase* MyPlayerState = GetPlayerState<APlayerStateBase>();
	if (MyPlayerState)
	{
		MyPlayerState->Server_UpdateStat(InPlayerStat);
		MyPlayerState->Server_UpdateCoin(InPlayerCoin);

		UpdatePlayerStatWidget();
	}
}

bool AInventoryController::C2S_RequestLoadPlayerState_Validate(FPlayerStatStructure InPlayerStat, int32 InPlayerCoin)
{
	return true;
}

void AInventoryController::C2S_PurchaseReroll_Implementation()
{
	APlayerStateBase* MyPlayerState = GetPlayerState<APlayerStateBase>();
	if (MyPlayerState && MyPlayerState->HasEnoughCoin(5))
	{
		MyPlayerState->DeductCoin(5);
	}
}

bool AInventoryController::C2S_PurchaseReroll_Validate()
{
	return true;
}

void AInventoryController::BeginPlay()
{
	Super::BeginPlay();

	if (!IsLocalPlayerController())
	{
		return;
	}
	
	if (InventoryComponent)
	{
		InventoryComponent->ItemWidgets.SetNum(InventoryComponent->Columns * InventoryComponent->Rows);
	}
	CreateInventoryWidget();

	if (UGodOfWeaponGameInstance* GameInstance = Cast<UGodOfWeaponGameInstance>(GetGameInstance()))
	{
		C2S_RequestLoadPlayerState(GameInstance->SavedPlayerStat, GameInstance->SavedPlayerGold);
	}
}

void AInventoryController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!IsLocalPlayerController())
	{
		return;
	}
	// UpdatePlayerStatWidget();
}

void AInventoryController::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	UpdatePlayerStatWidget();
}

void AInventoryController::CreateInventoryWidget()
{
	if (InventoryWidgetClass)
	{
		InventoryWidget = CreateWidget<UInventoryWidget>(this, InventoryWidgetClass);
		if (InventoryWidget)
		{
			InventoryWidget->AddToViewport();
			SetInputMode(FInputModeUIOnly());
			bShowMouseCursor = true;

			UpdatePlayerStatWidget();
		}
	}
}

void AInventoryController::C2S_PurchaseItem_Implementation(FName ItemID, int32 Price, EItemType Type)
{
	APlayerStateBase* MyPlayerState = GetPlayerState<APlayerStateBase>();
	if (!MyPlayerState || !MyPlayerState->HasEnoughCoin(Price))
	{
		return;
	}

	MyPlayerState->DeductCoin(Price);

	if (Type == EItemType::Consume)
	{
		MyPlayerState->ApplyConsumeEffect(ItemID);
	}
}

bool AInventoryController::C2S_PurchaseItem_Validate(FName ItemID, int32 Price, EItemType Type)
{
	return true;
}

void AInventoryController::UpdatePlayerStatWidget()
{
	if (InventoryWidget)
	{
		APlayerStateBase* MyPlayerState = GetPlayerState<APlayerStateBase>();
		if (MyPlayerState)
		{
			UE_LOG(LogTemp, Warning, TEXT("health: %d, coin: %d"), MyPlayerState->GetPlayerStat().CurrentHP, MyPlayerState->GetPlayerCoin());
			InventoryWidget->UpdatePlayerStatWidget(MyPlayerState->GetPlayerStat());
		}
	}	
}