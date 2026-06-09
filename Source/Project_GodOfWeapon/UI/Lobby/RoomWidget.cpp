// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void URoomWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void URoomWidget::SetInfo(FBlueprintSessionResult InSessionResult)
{
	SessionResult = InSessionResult;
	RefreshUI();
}

void URoomWidget::RefreshUI()
{
	FString SessionName;
	SessionResult.OnlineResult.Session.SessionSettings.Get("SESSION_NAME", OUT SessionName);

	const int32 CurrentPlayerCount = SessionResult.OnlineResult.Session.SessionSettings.NumPublicConnections - SessionResult.OnlineResult.Session.NumOpenPublicConnections;
	const int32 MaxPlayers = SessionResult.OnlineResult.Session.SessionSettings.NumPublicConnections;
	FString PlayerCountString = FString::Printf(TEXT("%d/%d"), CurrentPlayerCount, MaxPlayers);

	RoomNameTextBox->SetText(FText::FromString(SessionName));
	RoomNumOfPeopleTextBox->SetText(FText::FromString(PlayerCountString));
}