// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

class UCanvasPanel;
class UImage;

class UItemWidget;
class UPanelWidget;
class UDataTable;

UCLASS()
class PROJECT_GODOFWEAPON_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UCanvasPanel> CanvasPanel;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UImage> BackGroundImage;

	UPROPERTY(VisibleAnywhere,meta = (BindWidget))
	TObjectPtr<UPanelWidget> ItemPanel;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SpawnItem();

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, Category = "Data")
	TObjectPtr<UDataTable> ItemDataTable;

	UPROPERTY(EditAnywhere, Category = "Data")
	TSubclassOf<UItemWidget> ItemWidgetClass;
};