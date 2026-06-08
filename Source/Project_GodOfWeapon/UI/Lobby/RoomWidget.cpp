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

void URoomWidget::OnJoinClicked()
{
}
