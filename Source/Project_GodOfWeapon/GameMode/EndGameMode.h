// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EndGameMode.generated.h"

class UGodOfWeaponGameInstance;

UCLASS()
class PROJECT_GODOFWEAPON_API AEndGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Instance")
	TObjectPtr<UGodOfWeaponGameInstance> GameInstance;
};
