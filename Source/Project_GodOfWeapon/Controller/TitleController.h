// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "../Structs/PlayerStructs.h"
#include "../Structs/ItemStructs.h"
#include "../Enums/StageEnums.h"
#include "TitleController.generated.h"

class UTitleWidget;
class UCustomWidget;
class ULevelSettingWidget;

UCLASS()
class PROJECT_GODOFWEAPON_API ATitleController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void MoveCamera();

	UFUNCTION(BlueprintCallable)
	void CallCameraMoveFinished();

	void ShowTitleUI();

	void ShowCustomUI();

	void ShowLevelSettingUI();

	void RemoveTitleUI();

	void RemoveCustomUI();

	void RemoveLevelSettingUI();

	void RequestStartGame();

	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	TSubclassOf<UTitleWidget> TitleWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	TSubclassOf<UCustomWidget> CustomWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	TSubclassOf<ULevelSettingWidget> LevelSettingWidgetClass;

private:
	UPROPERTY()
	TObjectPtr<UTitleWidget> TitleWidget;

	UPROPERTY()
	TObjectPtr<UCustomWidget> CustomWidget;

	UPROPERTY()
	TObjectPtr<ULevelSettingWidget> LevelSettingWidget;

	class AActor* GetCameraByTag(const FName& InTag);

	void OnTimerDelayEnded();

	UFUNCTION()
	void HandleGameStart();

	UFUNCTION()
	void HandleCustomFinished(FCustomData InCustomData);

	UFUNCTION()
	void HandleEntry(const FSavedItemData& InItemData, EDifficulty InDifficulty);

private:
	template <typename T>
	T* CreateAndShowWidget(TSubclassOf<T> WidgetClass)
	{
		if (!WidgetClass)
		{
			return nullptr;
		}
		if (T* CreatedWidget = CreateWidget<T>(this, WidgetClass))
		{
			CreatedWidget->AddToViewport();
			return CreatedWidget;
		}
		return nullptr;
	}

	template <typename T>
	void RemoveWidget(TObjectPtr<T>& InWidget)
	{
		if (InWidget)
		{
			InWidget->RemoveFromParent();
			InWidget = nullptr;
		}
	}
};
