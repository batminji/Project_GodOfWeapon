// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InventoryController.generated.h"

class UInventoryComponent;

UCLASS()
class PROJECT_GODOFWEAPON_API AInventoryController : public APlayerController
{
	GENERATED_BODY()

public:
	AInventoryController();

	UPROPERTY(EditAnywhere)
	TObjectPtr<UInventoryComponent> InventoryComponent;
	
protected:
	virtual void BeginPlay() override;

	void CreateInventoryWidget();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	TSubclassOf<UUserWidget> InventoryWidgetClass;

	UPROPERTY()
	TObjectPtr<UUserWidget> InventoryWidget;
};
