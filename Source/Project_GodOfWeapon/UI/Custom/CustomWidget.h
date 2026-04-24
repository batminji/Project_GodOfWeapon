// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../../Structs/PlayerStructs.h"
#include "CustomWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCustomFinishedSignature, FCustomData, OutCustomData);

UCLASS()
class PROJECT_GODOFWEAPON_API UCustomWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintAssignable)
	FOnCustomFinishedSignature OnCustomFinished;

	UFUNCTION(BlueprintCallable, Category = "Events")
	void CallCustomFinished();

protected:
	UPROPERTY(BlueprintReadWrite, Category = "Custom")
	int32 CurrentHead = 15;

	UPROPERTY(BlueprintReadWrite, Category = "Custom")
	int32 CurrentChest = 1;

	UPROPERTY(BlueprintReadWrite, Category = "Custom")
	int32 CurrentHands = 1;

	UPROPERTY(BlueprintReadWrite, Category = "Custom")
	int32 CurrentLegs = 5;

	UPROPERTY(BlueprintReadWrite, Category = "Custom")
	int32 CurrentFoot = 1;
};
