// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryController.h"
#include "Blueprint/UserWidget.h"
#include "InventoryComponent.h"

AInventoryController::AInventoryController()
{
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));
}

void AInventoryController::BeginPlay()
{
	Super::BeginPlay();

	CreateInventoryWidget();
}

void AInventoryController::CreateInventoryWidget()
{
	if (InventoryWidgetClass)
	{
		InventoryWidget = CreateWidget<UUserWidget>(this, InventoryWidgetClass);
		if (InventoryWidget)
		{
			InventoryWidget->AddToViewport();
			SetInputMode(FInputModeUIOnly());
			bShowMouseCursor = true;
		}
	}
}
