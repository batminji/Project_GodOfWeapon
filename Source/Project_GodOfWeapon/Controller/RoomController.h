// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RoomController.generated.h"

class URoomHUDWidget;

UCLASS()
class PROJECT_GODOFWEAPON_API ARoomController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<class URoomHUDWidget> RoomHUDWidgetClass;

	void ShowRoomHUD();
};
