// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MakeRoomPopUpWidget.generated.h"

class UButton;
class UEditableTextBox;

UCLASS()
class PROJECT_GODOFWEAPON_API UMakeRoomPopUpWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UEditableTextBox> RoomNameEditableText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UEditableTextBox> NumOfPeopleEditableText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> CancleButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ConfirmButton;

	UFUNCTION()
	void OnCancleButtonClicked();

	UFUNCTION()
	void OnConfirmButtonClicked();
};
