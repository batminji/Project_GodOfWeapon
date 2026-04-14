// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemWidget.h"
#include "ItemDragDropOperation.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/SizeBox.h"
#include "Components/Border.h"
#include "Components/Image.h"
#include "InventoryController.h"
#include "InventoryComponent.h"

void UItemWidget::InitializeItem(const FItemStructure& InItemData)
{
	ItemData = InItemData;
	SetTileSize();

	Size = FVector2D(ItemData.Dimension.X * TileSize, ItemData.Dimension.Y * TileSize);

	if (BackGroundSizeBox)
	{
		BackGroundSizeBox->SetWidthOverride(Size.X);
		BackGroundSizeBox->SetHeightOverride(Size.Y);
	}

	if (ItemImage)
	{
		UObject* LoadedObject = ItemData.Icon.LoadSynchronous();
		UMaterialInterface* LoadedMaterial = Cast<UMaterialInterface>(LoadedObject);

		if (LoadedMaterial)
		{
			ItemImage->SetBrushFromMaterial(LoadedMaterial);
			ItemImage->SetOpacity(1.0f);
		}
	}

	UCanvasPanelSlot* ImageAsCanvasSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(ItemImage);
	ImageAsCanvasSlot->SetSize(Size);
}

void UItemWidget::NativeConstruct()
{
	Super::NativeConstruct();

	
}

void UItemWidget::SetTileSize()
{
	if (!InventoryController)
	{
		InventoryController = Cast<AInventoryController>(GetOwningPlayer());
	}
	TileSize = InventoryController->InventoryComponent->TileSize;
}

FReply UItemWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		return FReply::Handled().DetectDrag(TakeWidget(), EKeys::LeftMouseButton);
	}

	return FReply::Unhandled();
}

void UItemWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	UItemDragDropOperation* DragOp = Cast<UItemDragDropOperation>(UWidgetBlueprintLibrary::CreateDragDropOperation(UItemDragDropOperation::StaticClass()));

	if (DragOp)
	{
		DragOp->DraggedItemWidget = this;

		UItemWidget* DragVisualWidget = CreateWidget<UItemWidget>(InventoryController, GetClass());
		if (DragVisualWidget)
		{
			DragVisualWidget->InitializeItem(ItemData);
		}

		DragOp->DefaultDragVisual = DragVisualWidget;
		DragOp->Pivot = EDragPivot::MouseDown;

		OutOperation = DragOp;
	}
}
