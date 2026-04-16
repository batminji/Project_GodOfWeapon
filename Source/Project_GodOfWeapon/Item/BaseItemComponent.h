// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "ItemStructure.h"
#include "BaseItemComponent.generated.h"

UCLASS()
class PROJECT_GODOFWEAPON_API UBaseItemComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	UBaseItemComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TObjectPtr<UStaticMeshComponent> ItemMesh;

	UPROPERTY(EditAnywhere, blueprintReadWrite, Category = "Item", meta = (ExposeOnSpawn = "true"))
	EItemType ItemType;

	UPROPERTY(EditAnywhere, blueprintReadWrite, Category = "Item", meta = (ExposeOnSpawn = "true"))
	FItemStatStructure ItemStat;
	
};
