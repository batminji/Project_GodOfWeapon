// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class UItemWidget;
class UInventoryGridWidget;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_GODOFWEAPON_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventoryComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int32 Columns;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int32 Rows;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	float TileSize;

	TArray<UItemWidget*> ItemWidgets;

	bool AddedItem = false;

	TObjectPtr<UInventoryGridWidget> InventoryGridWidgetReference;

	bool TryAddItemAt(UItemWidget* InItemWidget, int32 TopLeftindex);
	bool IsRoomAvailable(UItemWidget* InItemWidget, int32 TopLeftIndex) const;

	FIntPoint IndexToTile(int32 InIndex) const;
	int32 TileToIndex(FIntPoint InTile) const;

	bool IsTileValid(FIntPoint InTile) const;

	bool GetResultAtIndex(int32 InIndex) const;

	UItemWidget* GetItemWidgetAtIndex(int32 InIndex) const;

	void AddItemWidget(UItemWidget* InItemWidget, int32 TopLeftIndex);

	TMap<UItemWidget*, FIntPoint> GetAllItemWidgets();

	void SetInventoryGridWidget(UInventoryGridWidget* InInventoryGridWidget);

	void RemoveItemWidget(UItemWidget* InItemWidget);

	void RefreshAllItems();

protected:
	virtual void BeginPlay() override;

	TMap<UItemWidget*, FIntPoint> AllItemWidgets;
};
