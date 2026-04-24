// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomWidget.h"

void UCustomWidget::NativeConstruct()
{
}

void UCustomWidget::CallCustomFinished()
{
	FCustomData CustomData;

	CustomData.HeadNumber = CurrentHead;
	CustomData.ChestNumber = CurrentChest;
	CustomData.HandsNumber = CurrentHands;
	CustomData.LegsNumber = CurrentLegs;
	CustomData.FootNumber = CurrentFoot;

	if(OnCustomFinished.IsBound())
	{
		OnCustomFinished.Broadcast(CustomData);
	}
}
