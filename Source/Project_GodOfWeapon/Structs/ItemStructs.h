// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ItemStructs.generated.h"

USTRUCT(BlueprintType)
struct FSavedItemData
{
	GENERATED_BODY()

	FSavedItemData()
		: ItemRowName(NAME_None), TopLeftTile(FIntPoint::ZeroValue), bIsRotated(false)
	{
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemRowName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FIntPoint TopLeftTile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsRotated;
};

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
struct FItemStat
{
	GENERATED_BODY()

	FItemStat()
		: Damage(0.0f), AttackRange(0.0f), AttackSpeed(0.0f), CooldownTime(0.0f)
	{
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CooldownTime;
};

USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY();

	FItemData()
		: ItemID(NAME_None), Type(EItemType::Sword), Name(FText::GetEmpty()), Desc(FText::GetEmpty()), Price(0),
		ItemActorClass(nullptr), Icon(nullptr), RotateIcon(nullptr), Dimension(FIntPoint(0, 0)), Stat()
		, ItemMesh(nullptr), ItemNiagara(nullptr), ArrowMesh(nullptr), ArrowNiagara(nullptr)
	{
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Desc;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Price;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftClassPtr<class ABaseItemActor> ItemActorClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UMaterialInterface> Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UMaterialInterface> RotateIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FIntPoint Dimension;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FItemStat Stat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UStaticMesh> ItemMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<class UNiagaraSystem> ItemNiagara;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arrow")
	TSoftObjectPtr<UStaticMesh> ArrowMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arrow")
	TSoftObjectPtr<class UNiagaraSystem> ArrowNiagara;
};
