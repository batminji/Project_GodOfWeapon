// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InventoryController.generated.h"

class UInventoryComponent;
class UInventoryWidget;
class UItemWidget;

UCLASS()
class PROJECT_GODOFWEAPON_API AInventoryController : public APlayerController
{
	GENERATED_BODY()

public:
	AInventoryController();

	UFUNCTION(Server, Reliable, WithValidation)
	void C2S_RequestNextStage();
	void C2S_RequestNextStage_Implementation();
	bool C2S_RequestNextStage_Validate();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TObjectPtr<UInventoryComponent> InventoryComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	TSubclassOf<UItemWidget> ItemWidgetClass;

	UPROPERTY()
	TObjectPtr<UItemWidget> ItemWidget;
	
protected:
	virtual void BeginPlay() override;

	void CreateInventoryWidget();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	TSubclassOf<UInventoryWidget> InventoryWidgetClass;

	UPROPERTY()
	TObjectPtr<UInventoryWidget> InventoryWidget;
};
