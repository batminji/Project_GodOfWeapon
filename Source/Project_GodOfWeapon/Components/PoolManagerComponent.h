// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "../Structs/MonsterStructs.h"
#include "PoolManagerComponent.generated.h"

class ABaseMonster;
class AInGameMode;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) , Blueprintable)
class PROJECT_GODOFWEAPON_API UPoolManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPoolManagerComponent();

	UFUNCTION(BlueprintCallable, Category = "Pool")
	void InitPool(const TArray<FName>& InNames, int32 InSpawnCount);

	UFUNCTION(BlueprintCallable, Category = "Pool")
	void ReturnToPool(ABaseMonster* InMonster);

	UFUNCTION(BlueprintCallable, Category = "Pool")
	ABaseMonster* GetFromPool(FName InName);

protected:
	virtual void BeginPlay() override;

	void SetGameMode();

	void SpawnMonsters(TSubclassOf<AActor> InSpawnClass, FName InMonsterName, FMonsterStat& InStat, int32 InSpawnCount);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Mode")
	TObjectPtr<AInGameMode> InGameMode;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Data Table")
	TObjectPtr<UDataTable> MonsterDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pool")
	TMap<FName, FMonsterPool> MonsterPoolMap;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
