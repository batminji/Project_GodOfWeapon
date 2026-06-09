// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyWidget.h"
#include "Components/Button.h"
#include "Components/WrapBox.h"
#include "RoomWidget.h"
#include "MakeRoomPopUpWidget.h"

void ULobbyWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

bool ULobbyWidget::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	SetInfo();

	return true;
}

void ULobbyWidget::SetInfo()
{
	if (!SessionItemWidgetClass)
	{
		return;
	}

	SessionItemWidgets.Empty();

	for (int i = 0; i < 10; ++i)
	{
		URoomWidget* ChildWidget = CreateWidget<URoomWidget>(GetWorld(), SessionItemWidgetClass);
		if (ChildWidget)
		{
			RoomWrapBox->AddChildToWrapBox(ChildWidget);
			SessionItemWidgets.Add(ChildWidget);
		}
	}

	RefreshList();
}

void ULobbyWidget::RefreshList()
{
	const int32 SessionLength = SessionResults.Num();
	UE_LOG(LogTemp, Warning, TEXT("SessionResults Length: %d"), SessionLength);

	for (int32 i = 0; i < SessionItemWidgets.Num(); ++i)
	{
		const int32 Index = i;

		if (Index < SessionLength)
		{
			SessionItemWidgets[Index]->SetVisibility(ESlateVisibility::Visible);
			FBlueprintSessionResult Result = SessionResults[Index];
			SessionItemWidgets[Index]->SetInfo(Result);
			UE_LOG(LogTemp, Warning, TEXT("Session Name: %s"), *Result.OnlineResult.Session.GetSessionIdStr());
		}
		else
		{
			SessionItemWidgets[Index]->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}