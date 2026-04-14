// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemWidget.h"
#include "ItemDragDropOperation.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void UItemWidget::NativeConstruct()
{
}

void UItemWidget::OnItemUpdated()
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
