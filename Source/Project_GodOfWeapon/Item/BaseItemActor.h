// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Structs/ItemStructs.h"
#include "../Enums/ItemEnums.h"
#include "BaseItemActor.generated.h"

class UStaticMeshComponent;
class USphereComponent;

UCLASS()
class PROJECT_GODOFWEAPON_API ABaseItemActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseItemActor();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TObjectPtr<UStaticMeshComponent> ItemMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TObjectPtr<USphereComponent> RangeSphereCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item", meta = (ExposeOnSpawn = "true"))
	EItemType ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item", meta = (ExposeOnSpawn = "true"))
	FItemStat ItemStat;

public:	
	virtual void Tick(float DeltaTime) override;

};
