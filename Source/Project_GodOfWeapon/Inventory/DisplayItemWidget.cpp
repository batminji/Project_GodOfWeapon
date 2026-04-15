// Fill out your copyright notice in the Description page of Project Settings.


#include "DisplayItemWidget.h"
#include "ItemWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/SizeBox.h"
#include "Components/Border.h"
#include "Components/CanvasPanelSlot.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Blueprint/DragDropOperation.h"
#include "InventoryController.h"
#include "InventoryComponent.h"

void UDisplayItemWidget::InitializeItem(const FItemStructure& InItemData)
{
	ItemData = InItemData;
	SetTileSize();

	Size = FVector2D(ItemData.Dimension.X * TileSize, ItemData.Dimension.Y * TileSize);

	if (ItemCoinText)
	{
		FText PriceText = FText::Format(FText::FromString("{0} G"), FText::AsNumber(ItemData.Price));
		ItemCoinText->SetText(PriceText);
	}

	if (ItemImage)
	{
		UObject* LoadedObject = ItemData.Icon.LoadSynchronous();
		if (UMaterialInterface* LoadedMaterial = Cast<UMaterialInterface>(LoadedObject))
		{
			ItemImage->SetBrushFromMaterial(LoadedMaterial);
			ItemImage->SetOpacity(1.0f);
		}
	}

	UCanvasPanelSlot* ImageAsCanvasSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(ItemImage);
	ImageAsCanvasSlot->SetSize(Size);
}

void UDisplayItemWidget::NativeConstruct()
{
	Super::NativeConstruct();

	InventoryController = Cast<AInventoryController>(GetOwningPlayer());
}

FReply UDisplayItemWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	return FReply::Handled().DetectDrag(TakeWidget(), EKeys::LeftMouseButton);
}

void UDisplayItemWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	if (ItemWidgetClass)
	{
		UItemWidget* DraggedItemWidget = CreateWidget<UItemWidget>(GetWorld(), ItemWidgetClass);
		if (DraggedItemWidget)
		{
			DraggedItemWidget->InitializeItem(ItemData);

			UDragDropOperation* DragOperation = NewObject<UDragDropOperation>();
			DragOperation->DefaultDragVisual = DraggedItemWidget;
			DragOperation->Payload = DraggedItemWidget;

			OutOperation = DragOperation;

			this->RemoveFromParent();
		}
	}
}

void UDisplayItemWidget::SetTileSize()
{
	if (!InventoryController)
	{
		InventoryController = Cast<AInventoryController>(GetOwningPlayer());
	}
	TileSize = InventoryController->InventoryComponent->TileSize;
}