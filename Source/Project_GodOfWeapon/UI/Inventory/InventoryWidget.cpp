// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"
#include "DisplayItemWidget.h"
#include "Engine/DataTable.h"
#include "Blueprint/DragDropOperation.h"
#include "Components/Overlay.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

#include "Project_GodOfWeapon/GodOfWeaponGameInstance.h"
#include "Kismet/GameplayStatics.h"

#include "../../Controller/InventoryController.h"
#include "../../Components/InventoryComponent.h"

void UInventoryWidget::OnNextStageClicked()
{
	InventoryController = Cast<AInventoryController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	InventoryComponent = InventoryController ? InventoryController->InventoryComponent : nullptr;

    if (InventoryComponent)
    {
        InventoryComponent->SaveInventoryToGameInstance();

		// Load the next level
        // UGameplayStatics::OpenLevel(GetWorld(), FName("TestMap"));
        UGameplayStatics::OpenLevel(GetWorld(), FName("InGameMap"));
	}
}

void UInventoryWidget::SpawnItem(bool bIsReroll)
{
    if (bIsReroll)
    {
        if (GameInstance && GameInstance->GetPlayerCoin() >= 5)
        {
            GameInstance->DeductCoin(5);
        }
        else
        {
            // Not enough money to spawn an item
            return;
        }
    }

    TArray<FItemData*> AllItems;
    ItemDataTable->GetAllRows<FItemData>(TEXT("Context"), AllItems);

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

    GameInstance = Cast<UGodOfWeaponGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

    if (NextStageButton)
    {
        NextStageButton->OnClicked.AddDynamic(this, &UInventoryWidget::OnNextStageClicked);
    }

    ItemSlots.Empty();
    ItemSlots.Add(SlotOverlay_0);
    ItemSlots.Add(SlotOverlay_1);
    ItemSlots.Add(SlotOverlay_2);
    ItemSlots.Add(SlotOverlay_3);
    ItemSlots.Add(SlotOverlay_4);

    SpawnItem(false);
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
        FText GoldText = FText::Format(FText::FromString("{0} G"), FText::AsNumber(GameInstance->GetPlayerCoin()));
        PlayerGoldText->SetText(GoldText);
    }
}
