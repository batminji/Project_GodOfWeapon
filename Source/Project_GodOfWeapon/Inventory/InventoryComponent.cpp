// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "ItemWidget.h"
#include "InventoryGridWidget.h"

#include "Project_GodOfWeapon/GodOfWeaponGameInstance.h"
#include "Kismet/GameplayStatics.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (AddedItem)
	{
		if (InventoryGridWidgetReference)
		{
			InventoryGridWidgetReference->Refresh();
		}
		AddedItem = false;
	}
}

bool UInventoryComponent::TryAddItemAt(UItemWidget* InItemWidget, int32 TopLeftindex)
{
	if (InItemWidget)
	{
		if (IsRoomAvailable(InItemWidget, TopLeftindex))
		{
			AddItemWidget(InItemWidget, TopLeftindex);
			return true;
		}
		return false;
	}
	return false;
}

bool UInventoryComponent::IsRoomAvailable(UItemWidget* InItemWidget, int32 TopLeftIndex) const
{
	FIntPoint Dimensions = InItemWidget->GetDimensions();
	FIntPoint Tile = IndexToTile(TopLeftIndex);

	for(int32 i = Tile.X; i < Tile.X + Dimensions.X; ++i)
	{
		for(int32 j = Tile.Y; j < Tile.Y + Dimensions.Y; ++j)
		{
			if (IsTileValid(FIntPoint(i, j)))
			{
				int32 Index = TileToIndex(FIntPoint(i, j));

				if (GetResultAtIndex(Index))
				{
					if (GetItemWidgetAtIndex(Index))
					{
						return false;
					}
				}
				else
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}
	}

	return true;
}

FIntPoint UInventoryComponent::IndexToTile(int32 InIndex) const
{
	return FIntPoint(InIndex % Columns, InIndex / Columns);
}

int32 UInventoryComponent::TileToIndex(FIntPoint InTile) const
{
	return InTile.X + InTile.Y * Columns;
}

bool UInventoryComponent::IsTileValid(FIntPoint InTile) const
{
	if(InTile.X >= 0 && InTile.Y >= 0 && InTile.X < Columns && InTile.Y < Rows)
	{
		return true;
	}
	return false;
}

bool UInventoryComponent::GetResultAtIndex(int32 InIndex) const
{
	if(ItemWidgets.IsValidIndex(InIndex))
	{
		return true;
	}
	return false;
}

UItemWidget* UInventoryComponent::GetItemWidgetAtIndex(int32 InIndex) const
{
	if(ItemWidgets.IsValidIndex(InIndex))
	{
		return ItemWidgets[InIndex];
	}
	return nullptr;
}

void UInventoryComponent::AddItemWidget(UItemWidget* InItemWidget, int32 TopLeftIndex)
{
	FIntPoint Dimensions = InItemWidget->GetDimensions();
	FIntPoint Tile = IndexToTile(TopLeftIndex);

	// UE_LOG(LogTemp, Warning, TEXT("Adding item widget at index %d with dimensions (%d, %d)"), TopLeftIndex, Dimensions.X, Dimensions.Y);

	for (int32 i = Tile.X; i < Tile.X + Dimensions.X; ++i)
	{
		for (int32 j = Tile.Y; j < Tile.Y + Dimensions.Y; ++j)
		{
			ItemWidgets[TileToIndex(FIntPoint(i, j))] = InItemWidget;
			// UE_LOG(LogTemp, Warning, TEXT("Setting ItemWidgets[%d] to %s"), TileToIndex(FIntPoint(i, j)), *InItemWidget->GetName());
		}
	}

	AddedItem = true;
}

TMap<UItemWidget*, FIntPoint> UInventoryComponent::GetAllItemWidgets()
{
	for(int32 i = 0; i < ItemWidgets.Num(); ++i)
	{
		if(ItemWidgets[i])
		{
			if (!AllItemWidgets.Contains(ItemWidgets[i]))
			{
				AllItemWidgets.Add(ItemWidgets[i], IndexToTile(i));
			}
		}
	}
	return AllItemWidgets;
}

void UInventoryComponent::SetInventoryGridWidget(UInventoryGridWidget* InInventoryGridWidget)
{
	InventoryGridWidgetReference = InInventoryGridWidget;
}

void UInventoryComponent::RemoveItemWidget(UItemWidget* InItemWidget)
{
	if (InItemWidget)
	{
		for(int32 i = 0; i < ItemWidgets.Num(); ++i)
		{
			if(ItemWidgets[i] == InItemWidget)
			{
				ItemWidgets[i] = nullptr;
			}
		}
	}
}

void UInventoryComponent::RefreshAllItems()
{
	AllItemWidgets.Empty();

	for (int32 i = 0; i < ItemWidgets.Num(); ++i)
	{
		if (ItemWidgets[i])
		{
			if (!AllItemWidgets.Contains(ItemWidgets[i]))
			{
				AllItemWidgets.Add(ItemWidgets[i], IndexToTile(i));
			}
		}
	}
}

void UInventoryComponent::SaveInventoryToGameInstance()
{
	UGodOfWeaponGameInstance* GameInstance = Cast<UGodOfWeaponGameInstance>(GetWorld()->GetGameInstance());
	if (!GameInstance)
	{
		return;
	}

	GameInstance->InventoryData.Empty();

	TMap<UItemWidget*, FIntPoint> AllItems = GetAllItemWidgets();

	for (auto& Item : AllItems)
	{
		UItemWidget* ItemWidget = Item.Key;
		FIntPoint TopLeftTile = Item.Value;

		if (ItemWidget)
		{
			FSavedItemData Data;
			Data.ItemRowName = ItemWidget->ItemData.ItemID;
			Data.TopLeftIndex = TileToIndex(TopLeftTile);
			Data.bIsRotated = ItemWidget->GetIsRotated();

			// UE_LOG(LogTemp, Warning, TEXT("Saving item %s at index %d with rotation %s"), *Data.ItemRowName.ToString(), Data.TopLeftIndex, Data.bIsRotated ? TEXT("true") : TEXT("false"));

			GameInstance->InventoryData.Add(Data);
		}
	}
}

// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	
}



