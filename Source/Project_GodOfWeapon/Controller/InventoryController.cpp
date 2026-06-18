// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryController.h"
#include "Blueprint/UserWidget.h"
#include "../Components/InventoryComponent.h"
#include "../UI/Inventory/InventoryWidget.h"
#include "../UI/Item/ItemWidget.h"

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

void AInventoryController::BeginPlay()
{
	Super::BeginPlay();

	InventoryComponent->ItemWidgets.SetNum(InventoryComponent->Columns * InventoryComponent->Rows);

	CreateInventoryWidget();
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
		}
	}
}
