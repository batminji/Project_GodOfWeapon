// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryController.h"
#include "Blueprint/UserWidget.h"
#include "../Components/InventoryComponent.h"
#include "../UI/Inventory/InventoryWidget.h"
#include "../UI/Item/ItemWidget.h"
#include "../UI/LoadingUserWidget.h"
#include "../Player/PlayerStateBase.h"
#include "../GameMode/InventoryGameMode.h"

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
}

void AInventoryController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!IsLocalPlayerController())
	{
		return;
	}
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

void AInventoryController::UpdatePlayerStatWidget()
{
	if (InventoryWidget)
	{
		APlayerStateBase* MyPlayerState = GetPlayerState<APlayerStateBase>();
		if (MyPlayerState)
		{
			InventoryWidget->UpdatePlayerStatWidget(MyPlayerState->GetPlayerStat());
		}
	}	
}