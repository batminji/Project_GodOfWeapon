// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryData.generated.h"

USTRUCT(BlueprintType)
struct FLines
{
	GENERATED_USTRUCT_BODY();

public:

	FLines();

	TArray<FVector2D> XLines;
	TArray<FVector2D> YLines;
};

USTRUCT(BlueprintType)
struct FMousePositionInTile
{
	GENERATED_USTRUCT_BODY();

public:

	FMousePositionInTile();

	bool Right;
	bool Down;
};

class PROJECT_GODOFWEAPON_API InventoryData
{
public:
	
};
