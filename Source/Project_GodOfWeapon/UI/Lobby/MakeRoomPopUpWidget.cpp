// Fill out your copyright notice in the Description page of Project Settings.


#include "MakeRoomPopUpWidget.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "../../GodOfWeaponGameInstance.h"

void UMakeRoomPopUpWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (CancleButton)
	{
		CancleButton->OnClicked.AddDynamic(this, &UMakeRoomPopUpWidget::OnCancleButtonClicked);
	}
	if (ConfirmButton)
	{
		ConfirmButton->OnClicked.AddDynamic(this, &UMakeRoomPopUpWidget::OnConfirmButtonClicked);
	}
}

void UMakeRoomPopUpWidget::OnCancleButtonClicked()
{
	RemoveFromParent();
}

void UMakeRoomPopUpWidget::OnConfirmButtonClicked()
{
	FName RoomName = FName(*RoomNameEditableText->GetText().ToString());

	int32 MaxPlayers = FCString::Atoi(*NumOfPeopleEditableText->GetText().ToString());

	UGodOfWeaponGameInstance* GameInstance = Cast<UGodOfWeaponGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		GameInstance->CreateServerSession(RoomName, MaxPlayers);
	}

	RemoveFromParent();
}
