// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FindSessionsCallbackProxy.h"
#include "RoomWidget.generated.h"

class UTextBlock;
class UButton;

UCLASS()
class PROJECT_GODOFWEAPON_API URoomWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void SetInfo(FBlueprintSessionResult InSessionResult);

	UFUNCTION(BlueprintCallable)
	void RefreshUI();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> RoomNameTextBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> RoomNumOfPeopleTextBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> JoinButton;

protected:
	UPROPERTY(BlueprintReadOnly)
	FBlueprintSessionResult SessionResult;
};
