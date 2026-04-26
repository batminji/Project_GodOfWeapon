// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "ItemDragDropOperation.generated.h"

class UItemWidget;

UCLASS()
class PROJECT_GODOFWEAPON_API UItemDragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, Category = "DragDrop", meta = (ExposeOnSpawn = "true"))
	TObjectPtr<UItemWidget> DraggedItemWidget;
};
