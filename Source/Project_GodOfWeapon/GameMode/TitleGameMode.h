// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "../Structs/PlayerStructs.h"
#include "TitleGameMode.generated.h"

class ATitleController;
class UTitleWidget;
class UCustomWidget;

UCLASS()
class PROJECT_GODOFWEAPON_API ATitleGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<ATitleController> TitleController;

	// Widget
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<UTitleWidget> TitleWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TObjectPtr<UTitleWidget> TitleWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<UCustomWidget> CustomWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TObjectPtr<UCustomWidget> CustomWidget;

	// Events
	UFUNCTION()
	void HandleMoveCameraEnded();

	UFUNCTION()
	void HandleGameStart();

	UFUNCTION()
	void HandleCustomFinished(FCustomData InCustomData);
};
