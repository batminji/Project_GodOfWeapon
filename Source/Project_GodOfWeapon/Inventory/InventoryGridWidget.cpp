// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryGridWidget.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanel.h"
#include "Components/Border.h"
#include "Components/CanvasPanelSlot.h"
#include "InventoryController.h"
#include "InventoryComponent.h"

void UInventoryGridWidget::NativeConstruct()
{
	Super::NativeConstruct();

	LineStruct = FLines();
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
	CreateLineSegments();
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

void UInventoryGridWidget::CreateLineSegments()
{
	for(int32 i = 0; i < Columns + 1; i++)
	{
		float X{ i * TileSize };
		LineStruct.XLines.Add(FVector2D(X, X));
		LineStruct.YLines.Add(FVector2D(0.0f, Rows * TileSize));
	}

	for (int32 i = 0; i < Rows + 1; i++)
	{
		float Y{ i * TileSize };
		LineStruct.XLines.Add(FVector2D(Y, Y));
		LineStruct.YLines.Add(FVector2D(0.0f, Columns * TileSize));
	}

	for(const FVector2D& Line : LineStruct.XLines)
	{
		StartX.Add(Line.X);
		EndX.Add(Line.Y);
	}

	for(const FVector2D& Line : LineStruct.YLines)
	{
		StartY.Add(Line.X);
		EndY.Add(Line.Y);
	}
}