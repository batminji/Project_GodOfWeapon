// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryGridWidget.generated.h"

class UCanvasPanel;
class UBorder;

UCLASS()
class PROJECT_GODOFWEAPON_API UInventoryGridWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UCanvasPanel* CanvasPanel;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UCanvasPanel* GridCanvasPanel;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UBorder* GridBorder;
};
