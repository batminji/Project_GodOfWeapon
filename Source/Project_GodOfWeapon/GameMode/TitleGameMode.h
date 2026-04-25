// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "../Structs/PlayerStructs.h"
#include "../Structs/ItemStructs.h"
#include "TitleGameMode.generated.h"

class ATitleController;
class UTitleWidget;
class UCustomWidget;
class ULevelSettingWidget;
class UDataTable;

UCLASS()
class PROJECT_GODOFWEAPON_API ATitleGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<ATitleController> TitleController;

	// Widget
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<UTitleWidget> TitleWidgetClass;

	TObjectPtr<UTitleWidget> TitleWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<UCustomWidget> CustomWidgetClass;

	TObjectPtr<UCustomWidget> CustomWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<ULevelSettingWidget> LevelSettingWidgetClass;

	TObjectPtr<ULevelSettingWidget> LevelSettingWidget;

	// Events
	UFUNCTION(BlueprintCallable)
	void HandleMoveCameraEnded();

	UFUNCTION(BlueprintCallable)
	void HandleGameStart();

	UFUNCTION(BlueprintCallable)
	void HandleCustomFinished(FCustomData InCustomData);

	UFUNCTION(BlueprintCallable)
	void HandleEntry(const FSavedItemData& InItemData, EDifficulty InDifficulty);

private:
	void CreateLevelWidget();
	void UpdateItemAndLevel(const FSavedItemData& InItemData, const EDifficulty InDifficulty);
};
