// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Structs/PlayerStructs.h"
#include "RoomCharacter.generated.h"

UCLASS()
class PROJECT_GODOFWEAPON_API ARoomCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ARoomCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void UpdatePlayerCustom(const FCustomData& InCustomData);

};
