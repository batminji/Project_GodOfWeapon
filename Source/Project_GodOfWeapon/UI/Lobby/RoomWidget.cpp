// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void URoomWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if(JoinButton)
	{
		JoinButton->OnClicked.AddDynamic(this, &URoomWidget::OnJoinClicked);
	}
}

void URoomWidget::SetRoomInfo(const FString& InRoomName, int32 InCurrentPlayers, int32 InMaxPlayers)
{
	if (RoomNameTextBox)
	{
		RoomNameTextBox->SetText(FText::FromString(InRoomName));
	}

	if (RoomNumOfPeopleTextBox)
	{
		FString PeopleString = FString::Printf(TEXT("%d/%d"), InCurrentPlayers, InMaxPlayers);
		RoomNumOfPeopleTextBox->SetText(FText::FromString(PeopleString));
	}
}

void URoomWidget::OnJoinClicked()
{
}
