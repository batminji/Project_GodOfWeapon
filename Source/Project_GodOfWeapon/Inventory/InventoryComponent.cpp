// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "ItemWidget.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

bool UInventoryComponent::TryAddItem(UItemWidget* InItemWidget)
{
	if (InItemWidget)
	{
		for(int32 i = 0; i < ItemWidgets.Num(); ++i)
		{
			if(IsRoomAvailable(InItemWidget, i))
			{
				AddItemWidget(InItemWidget, i);
				return true;
			}
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

	for (int32 i = Tile.X; i < Tile.X + Dimensions.X; ++i)
	{
		for (int32 j = Tile.Y; j < Tile.Y + Dimensions.Y; ++j)
		{
			ItemWidgets[TileToIndex(FIntPoint(i, j))] = InItemWidget;
		}
	}
}

// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	
}



