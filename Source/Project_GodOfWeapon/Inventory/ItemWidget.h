// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Project_GodOfWeapon/Item/ItemStructure.h"
#include "ItemWidget.generated.h"

class UCanvasPanel;
class USizeBox;
class UBorder;
class UImage;
class AInventoryController;

UCLASS()
class PROJECT_GODOFWEAPON_API UItemWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	FIntPoint GetDimensions() const { return Dimensions; }

	UPROPERTY(BlueprintReadOnly, Category = "Item")
	FItemStructure ItemData;

	UFUNCTION(BlueprintCallable, Category = "Item")
	void InitializeItem(const FItemStructure& InItemData);
	
protected:
	virtual void NativeConstruct() override;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UCanvasPanel> CanvasPanel;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<USizeBox> BackGroundSizeBox;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UBorder> BackGroundBorder;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UImage> ItemImage;

	TObjectPtr<AInventoryController> InventoryController;

	FIntPoint Dimensions;
	FVector2D Size;
	float TileSize = 50.0f;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
};
