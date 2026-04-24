// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TitleController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCameraMoveFinishedSignature);

UCLASS()
class PROJECT_GODOFWEAPON_API ATitleController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void MoveCamera();

	UPROPERTY(BlueprintAssignable)
	FOnCameraMoveFinishedSignature OnCameraMoveFinished;

	UFUNCTION(BlueprintCallable)
	void CallCameraMoveFinished();

private:
	class AActor* GetCameraByTag(const FName& InTag);

	void OnTimerDelayEnded();
};
