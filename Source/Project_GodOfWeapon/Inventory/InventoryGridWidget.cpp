// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryGridWidget.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanel.h"
#include "Components/Border.h"
#include "Components/CanvasPanelSlot.h"
#include "InventoryData.h"
#include "InventoryController.h"
#include "InventoryComponent.h"

void UInventoryGridWidget::NativeConstruct()
{
	Super::NativeConstruct();

	LineStruct = new FLines();
	StartX = {};
	StartY = {};
	EndX = {};
	EndY = {};
	
	TObjectPtr<AInventoryController> InventoryController = Cast<AInventoryController>(GetOwningPlayer());
	if (!InventoryController)
	{
		UE_LOG(LogTemp, Warning, TEXT("InventoryController is null"));
		return;
	}

	TObjectPtr<UInventoryComponent> InventoryComponent = InventoryController->InventoryComponent;
	if (InventoryComponent)
	{
		Columns = InventoryComponent->Columns;
		Rows = InventoryComponent->Rows;
		TileSize = InventoryComponent->TileSize;
	}

	UpdateGridSize();
}

int32 UInventoryGridWidget::NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	Super::NativePaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);

	return int32();
}

void UInventoryGridWidget::UpdateGridSize()
{
	float NewWidth = Columns * TileSize;
	float NewHeight = Rows * TileSize;

	TObjectPtr<UCanvasPanelSlot> BorderAsCanvasSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(GridBorder);
	BorderAsCanvasSlot->SetSize(FVector2D(NewWidth, NewHeight));
}
