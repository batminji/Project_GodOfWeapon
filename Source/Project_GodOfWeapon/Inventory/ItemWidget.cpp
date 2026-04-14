// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemWidget.h"
#include "Blueprint/DragDropOperation.h"
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

	InventoryController = Cast<AInventoryController>(GetOwningPlayer());

}

void UItemWidget::SetTileSize()
{
	if (!InventoryController)
	{
		InventoryController = Cast<AInventoryController>(GetOwningPlayer());
	}
	TileSize = InventoryController->InventoryComponent->TileSize;
}

void UItemWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	BackGroundBorder->SetBrushColor(FLinearColor(0.0f, 0.0f, 0.0f, 0.2f));
}

void UItemWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

	BackGroundBorder->SetBrushColor(FLinearColor(0.0f, 0.0f, 0.0f, 0.5f));
}

FReply UItemWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	return FReply::Handled().DetectDrag(TakeWidget(), EKeys::LeftMouseButton);
}

void UItemWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	BackGroundBorder->SetBrushColor(FLinearColor(0.0f, 0.0f, 0.0f, 0.5f));

	UpdateOriginalPosition();

	UDragDropOperation* DragOperation = NewObject<UDragDropOperation>();

	if (DragOperation)
	{
		DragOperation->DefaultDragVisual = this;

		DragOperation->Payload = this;

		InventoryController->InventoryComponent->RemoveItemWidget(this);
		OutOperation = DragOperation;

		this->RemoveFromParent();
	}
}

void UItemWidget::UpdateOriginalPosition()
{
	if (InventoryController && InventoryController->InventoryComponent)
	{
		FIntPoint* OriginalTile = InventoryController->InventoryComponent->GetAllItemWidgets().Find(this);
		if (OriginalTile)
		{
			OriginalTopLeftIndex = InventoryController->InventoryComponent->TileToIndex(*OriginalTile);
		}
	}
}
