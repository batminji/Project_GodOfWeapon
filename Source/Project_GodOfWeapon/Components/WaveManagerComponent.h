// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WaveManagerComponent.generated.h"

class AInGamePlayer;
class AInGameMode;
class UPoolManagerComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class PROJECT_GODOFWEAPON_API UWaveManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UWaveManagerComponent();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Initialize") // Blueprint
	void Init(int32 InStage, float InLevelMultiplier, UPoolManagerComponent* InPoolManagerRef);
	void Init_Implementation(int32 InStage, float InLevelMultiplier, UPoolManagerComponent* InPoolManagerRef);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Wave") // Blueprint
	void StartGame();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Initialize")
	void SetPlayer();
	void SetPlayer_Implementation();

	void SetGameMode();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	TObjectPtr<AInGamePlayer> Player;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Mode")
	TObjectPtr<AInGameMode> InGameMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UPoolManagerComponent> PoolManagerRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stage")
	int32 CurrentStage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stage")
	float LevelMultiplier;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
