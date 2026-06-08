// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyWidget.generated.h"

class UButton;
class UWrapBox;

UCLASS()
class PROJECT_GODOFWEAPON_API ULobbyWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> MakeRoomButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> SingleGameButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> RefreshButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UWrapBox> RoomWrapBox;

	// UFUNCTION()
	// void UpdateRoomList();

	void OnMakeRoomClicked();
	void OnSingleGameClicked();
	void OnRefreshClicked();
};