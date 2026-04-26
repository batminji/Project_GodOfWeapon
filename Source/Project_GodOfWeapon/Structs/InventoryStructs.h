// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryStructs.generated.h"

USTRUCT(BlueprintType)
struct FLines
{
	GENERATED_USTRUCT_BODY();

	FLines()
	{
	}

	TArray<FVector2D> XLines;
	TArray<FVector2D> YLines;
};

USTRUCT(BlueprintType)
struct FMousePositionInTile
{
	GENERATED_USTRUCT_BODY();

	FMousePositionInTile()
	{
	}

	bool Right;
	bool Down;
};