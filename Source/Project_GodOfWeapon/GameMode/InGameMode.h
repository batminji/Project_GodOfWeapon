// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "InGameMode.generated.h"

class UWaveManagerComponent;
class UPoolManagerComponent;
class UGodOfWeaponGameInstance;
class AInGamePlayer;
class UUserWidget;
class UNiagaraSystem;
class UStaticMesh;

UCLASS()
class PROJECT_GODOFWEAPON_API AInGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AInGameMode();

	virtual void Tick(float DeltaSeconds) override;

	virtual void PostLogin(APlayerController* InNewPlayer) override;

	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UWaveManagerComponent> WaveManagerComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPoolManagerComponent> PoolManagerComp;
	
	// Gettters
	int32 GetTotalDamage() const { return TotalDamage; }

	int32 GetTotalMonsterDefeated() const { return TotalMonsterDefeated; }

	// Setters
	void AddTotalMonsterDefeated(int32 InCount) { TotalMonsterDefeated += InCount; }

	void AddTotalDamage(int32 InDamage) { TotalDamage += InDamage; }

	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetLeftTime(float InTime) { LeftTime = InTime; }

	void SetCurrentStage(int32 InStage) { CurrentStage = InStage; }

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void Init();

	void UpdateGameStateLeftTime();
	void UpdateGameStateCurrentStage();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameInstance")
	TObjectPtr<UGodOfWeaponGameInstance> GameInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	TObjectPtr<AInGamePlayer> InGamePlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Total")
	int32 TotalDamage = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Total")
	int32 TotalMonsterDefeated = 0;

	float LeftTime = 0.0f;

	int32 CurrentStage = 1;

protected:
	UPROPERTY()
	TArray<class AInGameController*> SavedPlayers;

public:
	void OnPlayerSaveCompleted(class AInGameController* PlayerController);

	void StartSaveSequence();
};
