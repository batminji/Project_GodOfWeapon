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
	
protected:
	virtual void NativeConstruct() override;

	virtual int32 NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;
	
	TObjectPtr<UItemWidget> DraggedItem;
	TObjectPtr<UDragDropOperation> CurrentDragDropOperation;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	virtual bool NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	bool IsRoomAvailableForPayload(UItemWidget* InItemWidget) const;

	FMousePositionInTile MousePositionInTile;

	FMousePositionInTile GetMousePositionInTile(FVector2D InMousePosition);

	virtual FReply NativeOnPreviewKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

	virtual void NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	virtual void NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	FIntPoint DraggedItemTopLeftTile;

	bool bDrawDropLocation;

	void DrawBackGroundBox(UItemWidget* InItemWidget, FLinearColor InColor, const FGeometry& InGeometry, FVector2D InTopLeftCorner, FSlateWindowElementList& OutDrawElements, int32 LayedId) const;

	TObjectPtr<UObject> DraggedPayload;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UCanvasPanel> CanvasPanel;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UCanvasPanel> GridCanvasPanel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UBorder> GridBorder;

	UPanelSlot* PanelSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TObjectPtr<AInventoryController> InventoryController;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
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
