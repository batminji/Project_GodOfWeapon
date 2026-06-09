// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomController.h"
#include "../UI/Room/RoomHUDWidget.h"

void ARoomController::BeginPlay()
{
	Super::BeginPlay();
	
	if(IsLocalController())
	{
		ShowRoomHUD();
	}
}

void ARoomController::ShowRoomHUD()
{
	if (RoomHUDWidgetClass)
	{
		URoomHUDWidget* RoomHUD = CreateWidget<URoomHUDWidget>(this, RoomHUDWidgetClass);
		if (RoomHUD)
		{
			RoomHUD->AddToViewport();
			SetInputMode(FInputModeGameAndUI());
			bShowMouseCursor = true;
		}
	}
}
