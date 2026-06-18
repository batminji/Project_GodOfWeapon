// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Structs/PlayerStructs.h"
#include "InputActionValue.h"
#include "InGamePlayer.generated.h"

class UInputAction;

UCLASS()
class PROJECT_GODOFWEAPON_API AInGamePlayer : public ACharacter
{
	GENERATED_BODY()

public:
	AInGamePlayer();

	// Custom Data
	UFUNCTION(Server, Reliable, WithValidation)
	void C2S_SendCustomData(const FCustomData& InCustomData);
	void C2S_SendCustomData_Implementation(const FCustomData& InCustomData);
	bool C2S_SendCustomData_Validate(const FCustomData& InCustomData);

	UFUNCTION(Server, Reliable, WithValidation)
	void C2S_SendInventory(const TArray<FSavedItemData>& InItems);
	void C2S_SendInventory_Implementation(const TArray<FSavedItemData>& InItems);
	bool C2S_SendInventory_Validate(const TArray<FSavedItemData>& InItems);

	virtual void OnRep_PlayerState() override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void UpdatePlayerCustom(const FCustomData& InCustomData); // For Data Table Load

	// Item
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Item")
	void ApplyInventoryItems(const TArray<FSavedItemData>& InItems);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Item")
	bool AttachItemToPlayer(
		TSubclassOf<AActor> InItemBaseActorClass,
		EItemType InItemType,
		FItemStat InItemStat,
		UStaticMesh* InItemMesh,
		UNiagaraSystem* InItemNiagara,
		UStaticMesh* InArrowMesh,
		UNiagaraSystem* InArrowNiagara
	);

	UFUNCTION(BlueprintCallable, Category = "HP")
	void RecoverPlayerHP();

	UFUNCTION(Client, Reliable)
	void ClientExpandInventory();

	// Getters
	UFUNCTION(BlueprintPure, Category = "Player")
	FPlayerStatStructure GetCurrentPlayerStat() const;

	UFUNCTION(BlueprintPure, Category = "Player")
	int32 GetCoinCnt() const;

	int32 GetEarnedCoinCnt() const { return EarnedCoinCnt; }

	// Setters
	UFUNCTION(BlueprintCallable, Category = "Player")
	void SetCurrentPlayerStat(const FPlayerStatStructure& InCurrentPlayerStat);

	UFUNCTION(BlueprintCallable, Category = "Player")
	void SetCoinCnt(int32 InCoinCnt);

protected:
	virtual void BeginPlay() override;

	virtual void PawnClientRestart() override;

	void TryApplyCustomData();
	void TryApplyInventoryItems();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	int32 EarnedCoinCnt{ 0 };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	bool bIsDead{ false };

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_Move;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_Jump;

	void Move(const FInputActionValue& InValue);

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
