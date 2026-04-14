// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemWidget.h"
#include "ItemDragDropOperation.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/CanvasPanel.h"
#include "Components/SizeBox.h"
#include "Components/Border.h"
#include "Components/Image.h"

void UItemWidget::InitializeItem(const FItemStructure& InItemData)
{
	ItemData = InItemData;
	Dimensions = ItemData.Dimension;

	float CurrentTileX = (TileSize.X > 0.f) ? TileSize.X : 50.0f;
	float CurrentTileY = (TileSize.Y > 0.f) ? TileSize.Y : 50.0f;

	if (BackGroundSizeBox)
	{
		BackGroundSizeBox->SetWidthOverride(Dimensions.X * CurrentTileX);
		BackGroundSizeBox->SetHeightOverride(Dimensions.Y * CurrentTileY);
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
		else
		{
			ItemImage->SetOpacity(0.0f);
		}
	}
}

void UItemWidget::NativeConstruct()
{
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

		UUserWidget* DragVisualWidget = CreateWidget<UUserWidget>(GetWorld(), GetClass());


		DragOp->DefaultDragVisual = DragVisualWidget;
		DragOp->Pivot = EDragPivot::MouseDown;

		OutOperation = DragOp;
	}
}
