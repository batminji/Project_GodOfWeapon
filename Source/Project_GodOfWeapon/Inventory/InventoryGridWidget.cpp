// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryGridWidget.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/CanvasPanel.h"
#include "Components/Border.h"
#include "Components/CanvasPanelSlot.h"
#include "InventoryController.h"
#include "InventoryComponent.h"
#include "ItemDragDropOperation.h"

void UInventoryGridWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	InventoryController = Cast<AInventoryController>(GetOwningPlayer());
	
	if(!InventoryController)
	{
		UE_LOG(LogTemp, Warning, TEXT("InventoryController is null"));
		return;
	}

	SetGridData();
	UpdateGridSize();
	CreateLineSegments();
}

int32 UInventoryGridWidget::NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	Super::NativePaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);

	FPaintContext PaintContext(AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);

	RenderGridLines(PaintContext);

	return int32();
}

bool UInventoryGridWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	UItemDragDropOperation* ItemDropOp = Cast<UItemDragDropOperation>(InOperation);
	if (!ItemDropOp || !ItemDropOp->DraggedItemWidget) return false;

	FVector2D LocalMousePos = InGeometry.AbsoluteToLocal(InDragDropEvent.GetScreenSpacePosition());

	int32 TileColumn = FMath::FloorToInt(LocalMousePos.X / TileSize);
	int32 TileRow = FMath::FloorToInt(LocalMousePos.Y / TileSize);

	int32 TopLeftIndex = InventoryComponent->TileToIndex(FIntPoint(TileColumn, TileRow));

	if (InventoryComponent->TryAddItemAt(ItemDropOp->DraggedItemWidget, TopLeftIndex))
	{
		OnInventoryUpdated();
		return true;
	}

	return false;
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
	StartPoints.Empty();
	EndPoints.Empty();

	for (int32 i = 0; i <= Columns; i++)
	{
		float XPos = i * TileSize;
		StartPoints.Add(FVector2D(XPos, 0.0f));
		EndPoints.Add(FVector2D(XPos, Rows * TileSize));
	}

	for (int32 i = 0; i <= Rows; i++)
	{
		float YPos = i * TileSize;
		StartPoints.Add(FVector2D(0.0f, YPos));
		EndPoints.Add(FVector2D(Columns * TileSize, YPos));
	}
}

void UInventoryGridWidget::SetGridData()
{
	InventoryComponent = InventoryController->InventoryComponent;
	if (InventoryComponent)
	{
		Columns = InventoryComponent->Columns;
		Rows = InventoryComponent->Rows;
		TileSize = InventoryComponent->TileSize;
	}
}

void UInventoryGridWidget::RenderGridLines(FPaintContext& InPaintContext) const
{
	FLinearColor LineColor(0.5f, 0.5f, 0.5f, 1.0f); // Gray Color

	FVector2D GridTopLeftPos = GridBorder->GetCachedGeometry().GetLocalPositionAtCoordinates(FVector2D(0.0f, 0.0f));

	for (int32 i = 0; i < StartPoints.Num(); ++i)
	{
		UWidgetBlueprintLibrary::DrawLine(
			InPaintContext,
			StartPoints[i] + GridTopLeftPos,
			EndPoints[i] + GridTopLeftPos,
			LineColor, 1.0f);
	}
}

void UInventoryGridWidget::OnInventoryUpdated()
{
	TArray<UItemWidget*> Keys;
	InventoryComponent->GetAllItemWidgets().GetKeys(Keys);

	if (InventoryController->ItemWidgetClass)
	{
		InventoryController->ItemWidget = CreateWidget(GetWorld(), InventoryController->ItemWidgetClass);
		for (UItemWidget* AddedItem : Keys)
		{
			InventoryController->ItemWidget->SetOwningPlayer(GetOwningPlayer());
			int32 X = InventoryComponent->GetAllItemWidgets()[AddedItem].X * InventoryComponent->TileSize;
			int32 Y = InventoryComponent->GetAllItemWidgets()[AddedItem].Y * InventoryComponent->TileSize;

			PanelSlot = GridCanvasPanel->AddChild(InventoryController->ItemWidget);
			Cast<UCanvasPanelSlot>(PanelSlot)->SetAutoSize(true);
			Cast<UCanvasPanelSlot>(PanelSlot)->SetPosition(FVector2D(X, Y));
		}
	}
}