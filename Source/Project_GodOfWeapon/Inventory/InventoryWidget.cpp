// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"
#include "DisplayItemWidget.h"
#include "Engine/DataTable.h"
#include "Blueprint/DragDropOperation.h"
#include "Components/Overlay.h"
#include "Components/TextBlock.h"

#include "Project_GodOfWeapon/GodOfWeaponGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UInventoryWidget::SpawnItem()
{
    TArray<FItemStructure*> AllItems;
    ItemDataTable->GetAllRows<FItemStructure>(TEXT("Context"), AllItems);

    if (AllItems.Num() == 0) return;

    for (int32 i = 0; i < ItemSlots.Num(); ++i)
    {
        UOverlay* CurrentSlot = ItemSlots[i];
        if (CurrentSlot)
        {
            CurrentSlot->ClearChildren();

            int32 RandomIndex = FMath::RandRange(0, AllItems.Num() - 1);

            UDisplayItemWidget* NewItem = CreateWidget<UDisplayItemWidget>(this, DisplayItemWidgetClass);
            if (NewItem)
            {
                NewItem->InitializeItem(*AllItems[RandomIndex]);
                CurrentSlot->AddChild(NewItem);
            }
        }
    }
}

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

    ItemSlots.Empty();
    ItemSlots.Add(SlotOverlay_0);
    ItemSlots.Add(SlotOverlay_1);
    ItemSlots.Add(SlotOverlay_2);
    ItemSlots.Add(SlotOverlay_3);
    ItemSlots.Add(SlotOverlay_4);

    SpawnItem();

	GameInstance = Cast<UGodOfWeaponGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
}

void UInventoryWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);

    UpdatePlayerGoldText();
}

void UInventoryWidget::UpdatePlayerGoldText()
{
    if (GameInstance)
    {
        FText GoldText = FText::Format(FText::FromString("{0} G"), FText::AsNumber(GameInstance->PlayerMoney));
        PlayerGoldText->SetText(GoldText);
    }
}
