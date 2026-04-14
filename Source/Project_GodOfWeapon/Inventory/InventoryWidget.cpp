// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"
#include "ItemWidget.h"
#include "Components/PanelWidget.h"
#include "Engine/DataTable.h"

void UInventoryWidget::SpawnItem()
{
    ItemPanel->ClearChildren();

    TArray<FItemStructure*> AllItems;
    ItemDataTable->GetAllRows<FItemStructure>(TEXT("Context"), AllItems);

    if (AllItems.Num() == 0) return;

    for (int32 i = 0; i < 5; ++i)
    {
        int32 RandomIndex = FMath::RandRange(0, AllItems.Num() - 1);

        UItemWidget* NewItem = CreateWidget<UItemWidget>(this, ItemWidgetClass);
        if (NewItem)
        {
            NewItem->InitializeItem(*AllItems[RandomIndex]);
            ItemPanel->AddChild(NewItem);
        }
    }
}

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

    SpawnItem();
}
