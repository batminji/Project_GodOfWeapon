// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InGameController.generated.h"

class UInputMappingContext;
class UUserWidget;

UCLASS()
class PROJECT_GODOFWEAPON_API AInGameController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	
protected:
	virtual void OnPossess(APawn* InPawn) override;

	virtual void OnUnPossess() override;

	void ShowInGameMainWidget();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TSoftObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<UUserWidget> InGameMainWidgetClass;

	TObjectPtr<UUserWidget> InGameMainWidget;
};
