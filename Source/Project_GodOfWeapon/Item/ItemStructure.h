// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ItemStructure.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
    Sword       UMETA(DisplayName = "Sword"),
    Bow			UMETA(DisplayName = "Bow"),
    Hammer      UMETA(DisplayName = "Hammer"),
    Shield		UMETA(DisplayName = "Shield"),
	Consume 	UMETA(DisplayName = "Consume"),
};

USTRUCT(BlueprintType)
struct FItemStatStructure
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackRange = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackSpeed = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CooldownTime = 0.0f;
};

USTRUCT(BlueprintType)
struct FItemStructure : public FTableRowBase
{
	GENERATED_USTRUCT_BODY();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	EItemType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FText Desc;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TSoftObjectPtr<UMaterialInterface> Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TSoftObjectPtr<UMaterialInterface> RotateIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FIntPoint Dimension;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FItemStatStructure Stat;
	
	FItemStructure()
		: Type(EItemType::Sword), Name(FText::GetEmpty()), Desc(FText::GetEmpty()), 
		Icon(nullptr), Dimension(FIntPoint(0, 0))
	{
	}
};
