// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemStructure.h"
#include "BaseItemActor.generated.h"

class UStaticMeshComponent;
class UBoxComponent;

UCLASS()
class PROJECT_GODOFWEAPON_API ABaseItemActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseItemActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TObjectPtr<UBoxComponent> ItemCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TObjectPtr<UStaticMeshComponent> ItemMesh;

	UPROPERTY(EditAnywhere, blueprintReadWrite, Category = "Item", meta = (ExposeOnSpawn = "true"))
	EItemType ItemType;

	UPROPERTY(EditAnywhere, blueprintReadWrite, Category = "Item", meta = (ExposeOnSpawn = "true"))
	FItemStatStructure ItemStat;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
