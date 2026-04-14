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
#include "ItemWidget.h"

void UInventoryGridWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SetIsFocusable(true);
	
	InventoryController = Cast<AInventoryController>(GetOwningPlayer());
	
	if(!InventoryController)
	{
		UE_LOG(LogTemp, Warning, TEXT("InventoryController is null"));
		return;
	}

	SetGridData();
	UpdateGridSize();
	CreateLineSegments();

	InventoryComponent->SetInventoryGridWidget(this);
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

	if (InOperation->Payload)
	{
		UItemWidget* DroppedItem = Cast<UItemWidget>(InOperation->Payload);
		if (IsRoomAvailableForPayload(DroppedItem))
		{
			InventoryComponent->RefreshAllItems();
			InventoryComponent->TryAddItemAt(DroppedItem, InventoryComponent->TileToIndex(DraggedItemTopLeftTile));
		}
		else
		{
			InventoryComponent->TryAddItemAt(DroppedItem, DroppedItem->OriginalTopLeftIndex);
		}
		return true;
	}
	return false;
}

bool UInventoryGridWidget::NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragOver(InGeometry, InDragDropEvent, InOperation);

	if (InOperation->Payload)
	{
		DraggedItem = Cast<UItemWidget>(InOperation->Payload);

		FVector2D AbsolutePosition = InDragDropEvent.GetScreenSpacePosition();
		FVector2D LocalGridPosition = GridBorder->GetCachedGeometry().AbsoluteToLocal(AbsolutePosition);

		int32 MouseTileX = FMath::TruncToInt32(LocalGridPosition.X / InventoryComponent->TileSize);
		int32 MouseTileY = FMath::TruncToInt32(LocalGridPosition.Y / InventoryComponent->TileSize);

		bool bIsRight = GetMousePositionInTile(LocalGridPosition).Right;
		bool bIsDown = GetMousePositionInTile(LocalGridPosition).Down;

		FIntPoint Dimensions = DraggedItem->GetDimensions();

		int32 OffsetX = bIsRight ? (Dimensions.X - 1) / 2 : Dimensions.X / 2;
		int32 OffsetY = bIsDown ? (Dimensions.Y - 1) / 2 : Dimensions.Y / 2;

		int32 TargetTopLeftX = MouseTileX - OffsetX;
		int32 TargetTopLeftY = MouseTileY - OffsetY;

		TargetTopLeftX = FMath::Clamp(TargetTopLeftX, 0, Columns - Dimensions.X);
		TargetTopLeftY = FMath::Clamp(TargetTopLeftY, 0, Rows - Dimensions.Y);

		DraggedItemTopLeftTile = FIntPoint(TargetTopLeftX, TargetTopLeftY);

		return true;
	}
	return false;
}

bool UInventoryGridWidget::IsRoomAvailableForPayload(UItemWidget* InItemWidget) const
{
	if (InItemWidget)
	{
		return InventoryComponent->IsRoomAvailable(InItemWidget, InventoryComponent->TileToIndex(DraggedItemTopLeftTile));
	}
	return false;
}

FMousePositionInTile UInventoryGridWidget::GetMousePositionInTile(FVector2D InMousePosition)
{
	MousePositionInTile.Right = fmod(InMousePosition.X, InventoryComponent->TileSize) > (InventoryComponent->TileSize / 2);
	MousePositionInTile.Down = fmod(InMousePosition.Y, InventoryComponent->TileSize) > (InventoryComponent->TileSize / 2);

	return MousePositionInTile;
}

FReply UInventoryGridWidget::NativeOnPreviewKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if (InKeyEvent.GetKey() == EKeys::R)
	{
		if (DraggedItem)
		{
			DraggedItem->RotateItem();
			if (CurrentDragDropOperation)
			{
				UItemWidget* VisualDraggedItem = Cast<UItemWidget>(CurrentDragDropOperation->DefaultDragVisual);
				if(VisualDraggedItem)
				{
					VisualDraggedItem->InitializeItem(DraggedItem->ItemData);
				}
				return FReply::Handled();
			}
		}
	}

	return Super::NativeOnPreviewKeyDown(InGeometry, InKeyEvent);
}

void UInventoryGridWidget::NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragEnter(InGeometry, InDragDropEvent, InOperation);
	
	SetKeyboardFocus();

	UDragDropOperation* DraggedOperation = Cast<UDragDropOperation>(InOperation);
	if (DraggedOperation)
	{
		CurrentDragDropOperation = DraggedOperation;
	}
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
	FLinearColor LineColor(0.117f, 0.058f, 0.160f, 1.0f);

	FVector2D GridTopLeftPos = GridBorder->GetCachedGeometry().GetLocalPositionAtCoordinates(FVector2D(0.0f, 0.0f));

	for (int32 i = 0; i < StartPoints.Num(); ++i)
	{
		UWidgetBlueprintLibrary::DrawLine(
			InPaintContext,
			StartPoints[i] + GridTopLeftPos,
			EndPoints[i] + GridTopLeftPos,
			LineColor, true, 5.0f);
	}
}

void UInventoryGridWidget::Refresh()
{
	TArray<UItemWidget*> Keys;
	InventoryComponent->GetAllItemWidgets().GetKeys(Keys);

	for (UItemWidget* AddedItem : Keys)
	{
		if (AddedItem)
		{
			int32 X = InventoryComponent->GetAllItemWidgets()[AddedItem].X * InventoryComponent->TileSize;
			int32 Y = InventoryComponent->GetAllItemWidgets()[AddedItem].Y * InventoryComponent->TileSize;

			PanelSlot = GridCanvasPanel->AddChild(AddedItem);

			if (UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(PanelSlot))
			{
				CanvasSlot->SetAutoSize(true);
				CanvasSlot->SetPosition(FVector2D(X, Y));
			}
		}
	}
}