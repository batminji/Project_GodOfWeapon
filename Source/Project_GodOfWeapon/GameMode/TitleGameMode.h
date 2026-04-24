// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TitleGameMode.generated.h"

class ATitleController;

UCLASS()
class PROJECT_GODOFWEAPON_API ATitleGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<ATitleController> TitleController;

	UFUNCTION()
	void CreateCustomWidget();
};
