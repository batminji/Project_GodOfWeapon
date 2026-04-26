// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "../Item/ItemStructure.h"
#include "InGameMode.generated.h"

class UWaveManagerComponent;
class UPoolManagerComponent;
class UGodOfWeaponGameInstance;
class AInGamePlayer;
class UUserWidget;

UCLASS()
class PROJECT_GODOFWEAPON_API AInGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AInGameMode();
	
	// Gettters
	int32 GetTotalDamage() const { return TotalDamage; }

	int32 GetTotalMonsterDefeated() const { return TotalMonsterDefeated; }
protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void Init();

	UFUNCTION(BlueprintCallable)
	void UpdatePlayerStat();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Item")
	void SpawnItems();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Item")
	bool AttachItemToPlayer(TSubclassOf<AActor> InItemBaseActorClass, EItemType InItemType, FItemStat InItemStat);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UWaveManagerComponent> WaveManagerComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPoolManagerComponent> PoolManagerComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameInstance")
	TObjectPtr<UGodOfWeaponGameInstance> GameInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	TObjectPtr<AInGamePlayer> InGamePlayer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<UUserWidget> InGameMainWidgetClass;

	TObjectPtr<UUserWidget> InGameMainWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Total")
	int32 TotalDamage = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Total")
	int32 TotalMonsterDefeated = 0;
};
