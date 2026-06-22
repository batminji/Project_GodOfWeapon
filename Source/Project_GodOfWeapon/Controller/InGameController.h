// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "../Structs/PlayerStructs.h"
#include "InGameController.generated.h"

class UInputMappingContext;
class UUserWidget;

UCLASS()
class PROJECT_GODOFWEAPON_API AInGameController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	UFUNCTION(Server, Reliable, WithValidation)
	void C2S_RequestLoadPlayerState(FPlayerStatStructure InPlayerStat, int32 InPlayerCoin);
	void C2S_RequestLoadPlayerState_Implementation(FPlayerStatStructure InPlayerStat, int32 InPlayerCoin);
	bool C2S_RequestLoadPlayerState_Validate(FPlayerStatStructure InPlayerStat, int32 InPlayerCoin);

	UFUNCTION(Client, Reliable)
	void S2C_SavePlayerStateToInstance();
	void S2C_SavePlayerStateToInstance_Implementation();

	UFUNCTION(Server, Reliable, WithValidation)
	void C2S_NotifySaveFinished();
	void C2S_NotifySaveFinished_Implementation();
	bool C2S_NotifySaveFinished_Validate();
	
protected:
	virtual void OnPossess(APawn* InPawn) override;

	virtual void OnUnPossess() override;

	void SetupInputMappingContext();

	void ShowInGameMainWidget();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TSoftObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<UUserWidget> InGameMainWidgetClass;

	TObjectPtr<UUserWidget> InGameMainWidget;
};
