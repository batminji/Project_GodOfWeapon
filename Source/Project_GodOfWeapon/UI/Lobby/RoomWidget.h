// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RoomWidget.generated.h"

class UTextBlock;
class UButton;

UCLASS()
class PROJECT_GODOFWEAPON_API URoomWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	void SetRoomInfo(const FString& InRoomName, int32 InCurrentPlayers, int32 InMaxPlayers);

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> RoomNameTextBox;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> RoomNumOfPeopleTextBox;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> JoinButton;

	void OnJoinClicked();
};
