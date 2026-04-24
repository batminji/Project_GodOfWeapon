// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TitleController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMoveCameraEndedSignature);

UCLASS()
class PROJECT_GODOFWEAPON_API ATitleController : public APlayerController
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable)
	FOnMoveCameraEndedSignature OnMoveCameraEnded;
};
