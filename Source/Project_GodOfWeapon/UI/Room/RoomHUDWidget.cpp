// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomHUDWidget.h"

void URoomHUDWidget::CallStartButtonClicked()
{
	const FSavedItemData* OutItemData = nullptr;

	switch (PlayerStartItem)
	{
	case EItemType::Sword:
	{
		OutItemData = &BaseSwordItemData;
		break;
	}
	case EItemType::Bow:
	{
		OutItemData = &BaseBowItemData;
		break;
	}
	case EItemType::Hammer:
	{
		OutItemData = &BaseHammerItemData;
		break;
	}
	default:
		break;
	}

	if (OnStartButtonClicked.IsBound())
	{
		OnStartButtonClicked.Broadcast(*OutItemData, PlayerStartLevel);
	}
}