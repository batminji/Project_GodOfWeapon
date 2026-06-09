// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../../Structs/ItemStructs.h"
#include "../../Enums/StageEnums.h"
#include "RoomHUDWidget.generated.h"

class UButton;

UCLASS()
class PROJECT_GODOFWEAPON_API URoomHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> ExitButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> StartButton;

protected:
	UPROPERTY(BlueprintReadWrite, Category = "Player")
	EDifficulty PlayerStartLevel;

	UPROPERTY(BlueprintReadWrite, Category = "Player")
	EItemType PlayerStartItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
	FSavedItemData BaseSwordItemData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
	FSavedItemData BaseBowItemData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
	FSavedItemData BaseHammerItemData;
};
