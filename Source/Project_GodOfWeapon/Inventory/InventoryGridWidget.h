// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryGridWidget.generated.h"

class UCanvasPanel;
class UBorder;
struct FLines;

UCLASS()
class PROJECT_GODOFWEAPON_API UInventoryGridWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	virtual int32 NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UCanvasPanel* CanvasPanel;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UCanvasPanel* GridCanvasPanel;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UBorder* GridBorder;

	int32 Columns;
	int32 Rows;
	float TileSize;

	FLines* LineStruct;

	TArray<float> StartX;
	TArray<float> StartY;
	TArray<float> EndX;
	TArray<float> EndY;

	void UpdateGridSize();
};
