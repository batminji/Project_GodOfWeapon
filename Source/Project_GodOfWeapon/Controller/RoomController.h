// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "../Structs/PlayerStructs.h"
#include "RoomController.generated.h"

class URoomHUDWidget;

UCLASS()
class PROJECT_GODOFWEAPON_API ARoomController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ARoomController();

	virtual void BeginPlay() override;

	UFUNCTION(Server, Reliable)
	void ServerSendCustomData(const FCustomData& InCustomData);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<class URoomHUDWidget> RoomHUDWidgetClass;

	void ShowRoomHUD();

	class AActor* GetCameraByTag(const FName& InTag);
};
