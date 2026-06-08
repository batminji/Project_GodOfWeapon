// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyWidget.h"
#include "Components/Button.h"
#include "Components/WrapBox.h"

void ULobbyWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (MakeRoomButton)
	{
		MakeRoomButton->OnClicked.AddDynamic(this, &ULobbyWidget::OnMakeRoomClicked);
	}

	if(SingleGameButton)
	{
		SingleGameButton->OnClicked.AddDynamic(this, &ULobbyWidget::OnSingleGameClicked);
	}

	if(RefreshButton)
	{
		RefreshButton->OnClicked.AddDynamic(this, &ULobbyWidget::OnRefreshClicked);
	}
}

void ULobbyWidget::OnMakeRoomClicked()
{
}

void ULobbyWidget::OnSingleGameClicked()
{
}

void ULobbyWidget::OnRefreshClicked()
{
}
