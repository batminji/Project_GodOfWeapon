// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Project_GodOfWeapon/Item/ItemStructure.h"
#include "DisplayItemWidget.generated.h"

class UTextBlock;
class UImage;
class USizeBox;
class UBorder;
class UItemWidget;
class UDragDropOperation;
class AInventoryController;

UCLASS()
class PROJECT_GODOFWEAPON_API UDisplayItemWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void InitializeItem(const FItemStructure& InItemData);

protected:
	virtual void NativeConstruct() override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

	UPROPERTY(meta = (BindWidget))
	UImage* ItemImage;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ItemCoinText;

	UPROPERTY(EditDefaultsOnly, Category = "Item")
	TSubclassOf<UItemWidget> ItemWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
	FItemStructure ItemData;

	TObjectPtr<AInventoryController> InventoryController;

	FVector2D Size;
	float TileSize;

	void SetTileSize();
};
