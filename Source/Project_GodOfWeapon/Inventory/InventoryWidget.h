// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

class UCanvasPanel;
class UImage;
class UButton;

class UItemWidget;
class UPanelWidget;
class UDataTable;
class UOverlay;

UCLASS()
class PROJECT_GODOFWEAPON_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UCanvasPanel> CanvasPanel;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UImage> BackGroundImage;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UOverlay> SlotOverlay_0;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UOverlay> SlotOverlay_1;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UOverlay> SlotOverlay_2;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UOverlay> SlotOverlay_3;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UOverlay> SlotOverlay_4;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UButton> SpawnItemButton;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SpawnItem();

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, Category = "Data")
	TObjectPtr<UDataTable> ItemDataTable;

	UPROPERTY(EditAnywhere, Category = "Data")
	TSubclassOf<UItemWidget> ItemWidgetClass;

	TArray<UOverlay*> ItemSlots;
};