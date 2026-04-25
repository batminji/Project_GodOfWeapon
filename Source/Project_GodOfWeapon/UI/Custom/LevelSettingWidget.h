// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../../Structs/ItemStructs.h"
#include "../../Enums/StageEnums.h"
#include "../../Item/ItemStructure.h"
#include "LevelSettingWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStartButtonClickedSignature, const FSavedItemData&, OutStartItemData, EDifficulty, OutLevel);

UCLASS()
class PROJECT_GODOFWEAPON_API ULevelSettingWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnStartButtonClickedSignature OnStartButtonClicked;

	UFUNCTION(BlueprintCallable, Category = "Events")
	void CallStartButtonClicked();
	
protected:
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadWrite, Category = "Player")
	EDifficulty PlayerStartLevel;

	UPROPERTY(BlueprintReadWrite, Category = "Player")
	EItemType PlayerStartItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
	FSavedItemData BaseSwordItemData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
	FSavedItemData BaseBowItemData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
	FSavedItemData BaseHammerItemData;
};
