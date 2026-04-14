// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryData.h"
#include "Project_GodOfWeapon/Item/ItemStructure.h"
#include "InventoryGridWidget.generated.h"

class UCanvasPanel;
class UBorder;
class AInventoryController;
class UInventoryComponent;
class UItemWidget;

UCLASS()
class PROJECT_GODOFWEAPON_API UInventoryGridWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void Refresh();

	bool bDropped = false;
	
protected:
	virtual void NativeConstruct() override;

	virtual int32 NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	virtual bool NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	bool IsRoomAvailableForPayload(UItemWidget* InItemWidget) const;

	FMousePositionInTile MousePositionInTile;

	FMousePositionInTile GetMousePositionInTile(FVector2D InMousePosition);

	FIntPoint DraggedItemTopLeftTile;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UCanvasPanel> CanvasPanel;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UCanvasPanel> GridCanvasPanel;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UBorder> GridBorder;

	UPanelSlot* PanelSlot;

	TObjectPtr<AInventoryController> InventoryController;
	TObjectPtr<UInventoryComponent> InventoryComponent;

	int32 Columns;
	int32 Rows;
	float TileSize;

	FLines* LineStructData;

	TArray<FVector2D> StartPoints;
	TArray<FVector2D> EndPoints;

	void UpdateGridSize();
	void CreateLineSegments();
	void SetGridData();
	void RenderGridLines(FPaintContext& InPaintContext) const;
};
