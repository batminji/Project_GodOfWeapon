// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Structs/ItemStructs.h"
#include "../Enums/ItemEnums.h"
#include "BaseItemActor.generated.h"

class UStaticMeshComponent;
class USphereComponent;
class AInGamePlayer;
class USpringArmComponent;
class UChildActorComponent;
class UNiagaraComponent;
class UNiagaraSystem;
class UStaticMesh;

UCLASS()
class PROJECT_GODOFWEAPON_API ABaseItemActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseItemActor();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void InitItem(
		EItemType InItemType, 
		FItemStat InItemStat, 
		USpringArmComponent* InOwnerSpringArm, 
		UChildActorComponent* InOwnerChildActorComponent, 
		UStaticMesh* InItemMesh,
		UNiagaraSystem* InItemNiagara,
		UStaticMesh* InArrowMesh,
		UNiagaraSystem* InArrowNiagara
	);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetPlayer();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "State")
	void Idle();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "State")
	void Approach();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "State")
	void Attack();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "State")
	void Returning();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "State")
	void Cooldown();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "State")
	void OnCooldownFinished();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Check")
	bool IsCanAttack();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Check")
	bool IsMonsterInRange();

	UFUNCTION(BlueprintCallable, Category = "Check")
	void FindTargetInRange(AActor*& OutTargetActor, FVector& OutTargetLocation);

	void UpdateShortRangeItemStat(FItemStat InStat);

	void UpdateLongRangeItemStat(FItemStat InStat);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TObjectPtr<UStaticMeshComponent> ItemMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item", meta = (ExposeOnSpawn = "true"))
	EItemType ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item", meta = (ExposeOnSpawn = "true"))
	FItemStat ItemStat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	EItemState ItemCurrentState = EItemState::Idle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	TObjectPtr<AInGamePlayer> InGamePlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	bool bCanAttack = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Owner")
	TObjectPtr<USpringArmComponent> OwnerSpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Owner")
	TObjectPtr<UChildActorComponent> OwnerChildActor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	UNiagaraComponent* Niagara;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arrow")
	TObjectPtr<UStaticMesh> ArrowStaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arrow")
	TObjectPtr<UNiagaraSystem> ArrowNiagaraSystem;

public:	
	virtual void Tick(float DeltaTime) override;

};
