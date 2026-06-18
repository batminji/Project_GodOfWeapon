// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

class UCanvasPanel;
class UImage;
class UButton;
class UTextBlock;

class UDisplayItemWidget;
class UPanelWidget;
class UDataTable;
class UOverlay;

class APlayerStateBase;
class AInventoryController;
class UInventoryComponent;

UCLASS()
class PROJECT_GODOFWEAPON_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void OnNextStageClicked();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SpawnItem(bool bIsReroll);

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

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UButton> NextStageButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget));
	TObjectPtr<UTextBlock> PlayerGoldText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> LeftTimeText;

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Data")
	TObjectPtr<UDataTable> ItemDataTable;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<class UDisplayItemWidget> DisplayItemWidgetClass;

	TArray<UOverlay*> ItemSlots;

	TObjectPtr<APlayerStateBase> PlayerState;
	TObjectPtr<AInventoryController> InventoryController;
	TObjectPtr<UInventoryComponent> InventoryComponent;

	void UpdatePlayerGoldText();
};