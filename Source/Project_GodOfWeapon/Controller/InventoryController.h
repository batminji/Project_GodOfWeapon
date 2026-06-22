// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InventoryController.generated.h"

class UInventoryComponent;
class UInventoryWidget;
class UItemWidget;
class ULoadingUserWidget;

UCLASS()
class PROJECT_GODOFWEAPON_API AInventoryController : public APlayerController
{
	GENERATED_BODY()

public:
	AInventoryController();

	UFUNCTION(Server, Reliable, WithValidation)
	void C2S_RequestNextStage();
	void C2S_RequestNextStage_Implementation();
	bool C2S_RequestNextStage_Validate();

	UFUNCTION(Client, Reliable)
	void S2C_ShowLoadingScreen();
	void S2C_ShowLoadingScreen_Implementation();

	UFUNCTION(Client, Reliable)
	void S2C_UpdatePlayerInventory();
	void S2C_UpdatePlayerInventory_Implementation();

	UFUNCTION(Server, Reliable, WithValidation)
	void C2S_NotifySaveFinished();
	void C2S_NotifySaveFinished_Implementation();
	bool C2S_NotifySaveFinished_Validate();

	UFUNCTION(Server, Reliable, WithValidation)
	void C2S_RequestLoadPlayerState(FPlayerStatStructure InPlayerStat, int32 InPlayerCoin);
	void C2S_RequestLoadPlayerState_Implementation(FPlayerStatStructure InPlayerStat, int32 InPlayerCoin);
	bool C2S_RequestLoadPlayerState_Validate(FPlayerStatStructure InPlayerStat, int32 InPlayerCoin);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TObjectPtr<UInventoryComponent> InventoryComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	TSubclassOf<UItemWidget> ItemWidgetClass;

	UPROPERTY()
	TObjectPtr<UItemWidget> ItemWidget;
	
protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void OnRep_PlayerState() override;

	void CreateInventoryWidget();

	void UpdatePlayerStatWidget();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UInventoryWidget> InventoryWidgetClass;

	UPROPERTY()
	TObjectPtr<UInventoryWidget> InventoryWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<ULoadingUserWidget> LoadingScreenWidgetClass;
};
