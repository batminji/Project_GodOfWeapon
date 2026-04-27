// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Structs/MonsterStructs.h"
#include "BaseMonster.generated.h"

class AMonsterAIController;
class AInGameMode;

UCLASS()
class PROJECT_GODOFWEAPON_API ABaseMonster : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseMonster();

	UFUNCTION(BlueprintCallable, Category = "Monster")
	void DisableMonster();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Monster")
	void EnableMonster(float InStatMultiplier, float InLevelMultiplier);
	virtual void EnableMonster_Implementation(float InStatMultiplier, float InLevelMultiplier);

	UFUNCTION(BlueprintCallable, Category = "State")
	void EndSpawning();

	UFUNCTION(BlueprintCallable, Category = "State")
	void EndDying();

	UFUNCTION(BlueprintCallable, Category = "State")
	void DieMonster();

	UFUNCTION(BlueprintImplementableEvent, Category = "Coin")
	void CreateCoinActors(int32 InCount);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Damage")
	void CreateDamageTextWidget(int32 InDamage);

	UFUNCTION(BlueprintCallable, Category = "Damage")
	void TakeDamage(float InDamage);

	// Setters
	void SetBaseMonsterStat(const FMonsterStat& InBaseMonsterStat) { BaseMonsterStat = InBaseMonsterStat; }

protected:
	virtual void BeginPlay() override;

	virtual void PossessedBy(AController* NewController) override;

	void SetGameMode();

	void UpdateBBSpawning();

	void UpdateMonsterHP(int32 InDamage);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Game Mode")
	TObjectPtr<AInGameMode> InGameMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	TObjectPtr<AMonsterAIController> AIController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (ExposeOnSpawn = "true"))
	FMonsterStat BaseMonsterStat;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Stats")
	FMonsterStat CurrentMonsterStat;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "State")
	bool bIsDead = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "State")
	bool bIsSpawning = false;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
