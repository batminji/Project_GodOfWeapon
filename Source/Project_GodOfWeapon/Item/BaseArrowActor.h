// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseArrowActor.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class UNiagaraComponent;
class UProjectileMovementComponent;

UCLASS()
class PROJECT_GODOFWEAPON_API ABaseArrowActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseArrowActor();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Init")
	void InitArrow(float InAttackDamage, UStaticMesh* InArrowMesh, UNiagaraSystem* InArrowNiagara);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UBoxComponent> BoxComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UStaticMeshComponent> ArrowMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UNiagaraComponent> NiagaraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float AttackDamage;

public:	
	virtual void Tick(float DeltaTime) override;

};
