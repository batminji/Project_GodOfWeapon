// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

class UCanvasPanel;
class UImage;

UCLASS()
class PROJECT_GODOFWEAPON_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UCanvasPanel* CanvasPanel;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UImage* BackGroundImage;

protected:
	virtual void NativeConstruct() override;
};