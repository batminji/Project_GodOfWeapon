// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WaveManagerComponent.generated.h"

class AInGamePlayer;
class AInGameMode;
class UPoolManagerComponent;
class UDataTable;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStageEventSignature);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class PROJECT_GODOFWEAPON_API UWaveManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UWaveManagerComponent();

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Events")
	FOnStageEventSignature OnStageClear;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Events")
	FOnStageEventSignature OnStageFailed;

	UFUNCTION(BlueprintCallable, Category = "Initialize")
	void Init(int32 InStage, float InLevelMultiplier, UPoolManagerComponent* InPoolManagerRef);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Wave") // Blueprint
	void StartGame();

	UFUNCTION(BlueprintCallable, Category = "Wave")
	void GoNextStage();

	UFUNCTION(BlueprintCallable, Category = "Wave")
	void GoEnding();

	// Getters
	UFUNCTION(BlueprintPure, Category = "Monster")
	int32 GetCurrentAliveCount() const { return CurrentAliveCount; }

	UFUNCTION(BlueprintCallable, Category = "Monster")
	void DecreaseCurrentAliveCount() { CurrentAliveCount = FMath::Max(0, CurrentAliveCount - 1); }

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Initialize")
	void SetPlayer();
	void SetPlayer_Implementation();

	void SetGameMode();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	TObjectPtr<AInGamePlayer> InGamePlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Mode")
	TObjectPtr<AInGameMode> InGameMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UPoolManagerComponent> PoolManagerRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stage")
	int32 CurrentStage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stage")
	TArray<FName> SpawnMonsterNames;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stage")
	int32 MaxWaveCount = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stage")
	float LevelMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stage")
	float StatMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stage")
	float SpawnInterval;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stage")
	float WaveTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster")
	int32 MaxAliveCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster")
	int32 CurrentAliveCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timer")
	FTimerHandle SpawnMonsterTimeHandler;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timer")
	FTimerHandle EndWaveTimeHandler;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timer")
	FTimerHandle PlayerRecoverTimerHandler;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Table")
	TObjectPtr<UDataTable> WaveDataTable;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
