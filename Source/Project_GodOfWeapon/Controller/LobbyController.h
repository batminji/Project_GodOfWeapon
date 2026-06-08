// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LobbyController.generated.h"

class ULobbyWidget;

UCLASS()
class PROJECT_GODOFWEAPON_API ALobbyController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<ULobbyWidget> LobbyWidgetClass;
	
private:
	UPROPERTY()
	TObjectPtr<ULobbyWidget> LobbyWidget;
};
