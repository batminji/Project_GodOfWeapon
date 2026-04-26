// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PoolManagerComponent.generated.h"

class ABaseMonster;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) , Blueprintable)
class PROJECT_GODOFWEAPON_API UPoolManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPoolManagerComponent();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Pool") // Blueprint
	void ReturnToPool(ABaseMonster* InMonster);

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
