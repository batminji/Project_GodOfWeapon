// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomController.h"
#include "Kismet/GameplayStatics.h"
#include "../UI/Room/RoomHUDWidget.h"
#include "Camera/CameraActor.h"
#include "../Player/RoomCharacter.h"
#include "../GodOfWeaponGameInstance.h"

ARoomController::ARoomController()
{
	bAutoManageActiveCameraTarget = false;
}

void ARoomController::BeginPlay()
{
	Super::BeginPlay();

	AActor* MainCamera = GetCameraByTag(TEXT("MainCamera"));
	if (MainCamera)
	{
		SetViewTarget(MainCamera);
	}
	
	if(!IsLocalController())
	{
		return;
	}

	ShowRoomHUD();

	UGodOfWeaponGameInstance* GameInstance = Cast<UGodOfWeaponGameInstance>(GetGameInstance());
	if(GameInstance)
	{
		FCustomData CustomData = GameInstance->GetPlayerCustomData();
		UE_LOG(LogTemp, Log, TEXT("Player Custom Data - Head: %d, Chest: %d, Hands: %d, Legs: %d, Foot: %d"), 
			CustomData.HeadNumber, CustomData.ChestNumber, CustomData.HandsNumber, CustomData.LegsNumber, CustomData.FootNumber);
		ServerSendCustomData(CustomData);
	}
}

void ARoomController::ServerSendCustomData_Implementation(const FCustomData& InCustomData)
{
	ARoomCharacter* RoomCharacter = Cast<ARoomCharacter>(GetPawn());

	if (RoomCharacter)
	{
		RoomCharacter->UpdatePlayerCustom(InCustomData);
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

AActor* ARoomController::GetCameraByTag(const FName& InTag)
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACameraActor::StaticClass(), FoundActors);

	for (AActor* Actor : FoundActors)
	{
		if (Actor->ActorHasTag(InTag))
		{
			return Actor;
		}
	}

	return nullptr;
}