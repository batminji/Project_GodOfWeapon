// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CoinActor.generated.h"

class UBoxComponent;
class UWidgetComponent;
class AInGamePlayer;

UCLASS()
class PROJECT_GODOFWEAPON_API ACoinActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ACoinActor();

protected:
	virtual void BeginPlay() override;

	void Init();

	UFUNCTION(BlueprintImplementableEvent)
	void MoveToPlayer();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UBoxComponent> BoxComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UWidgetComponent> WidgetComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector SpawnLocation = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<AInGamePlayer> InGamePlayer;

public:	
	virtual void Tick(float DeltaTime) override;

};
