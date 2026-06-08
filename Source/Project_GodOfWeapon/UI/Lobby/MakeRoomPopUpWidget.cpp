// Fill out your copyright notice in the Description page of Project Settings.


#include "MakeRoomPopUpWidget.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"

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
}

void UMakeRoomPopUpWidget::OnConfirmButtonClicked()
{
}
