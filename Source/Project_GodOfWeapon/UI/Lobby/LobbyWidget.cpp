// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyWidget.h"
#include "Components/Button.h"
#include "Components/WrapBox.h"
#include "RoomWidget.h"
#include "MakeRoomPopUpWidget.h"
#include "OnlineSessionSettings.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "../../GodOfWeaponGameInstance.h"

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

void ULobbyWidget::UpdateRoomList(bool bSuccess)
{
	if (!bSuccess)
	{
		return;
	}

	UGodOfWeaponGameInstance* GameInstance = Cast<UGodOfWeaponGameInstance>(GetGameInstance());
	if (!GameInstance || !GameInstance->SessionSearch)
	{
		return;
	}

	for (const FOnlineSessionSearchResult& Result : GameInstance->SessionSearch->SearchResults)
	{
		if (Result.IsValid() && RoomWidgetClass)
		{
			URoomWidget* RoomWidget = CreateWidget<URoomWidget>(this, RoomWidgetClass);
			if (RoomWidget)
			{
				FString RoomNameStr;
				Result.Session.SessionSettings.Get(FName("ROOM_NAME"), RoomNameStr);

				int32 CurrentPlayers = Result.Session.SessionSettings.NumPublicConnections - Result.Session.NumOpenPublicConnections;
				int32 MaxPlayers = Result.Session.SessionSettings.NumPublicConnections;

				RoomWidget->SetRoomInfo(RoomNameStr, CurrentPlayers, MaxPlayers);

				RoomWrapBox->AddChildToWrapBox(RoomWidget);
			}
		}
	}
}

void ULobbyWidget::OnMakeRoomClicked()
{
	if (MakeRoomPopUpWidgetClass)
	{
		UMakeRoomPopUpWidget* MakeRoomPopUp = CreateWidget<UMakeRoomPopUpWidget>(this, MakeRoomPopUpWidgetClass);
		if(MakeRoomPopUp)
		{
			MakeRoomPopUp->AddToViewport();
		}
	}
}

void ULobbyWidget::OnSingleGameClicked()
{
}

void ULobbyWidget::OnRefreshClicked()
{
	RoomWrapBox->ClearChildren();

	UGodOfWeaponGameInstance* GameInstance = Cast<UGodOfWeaponGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		GameInstance->FindServerSessions();
	}
}
