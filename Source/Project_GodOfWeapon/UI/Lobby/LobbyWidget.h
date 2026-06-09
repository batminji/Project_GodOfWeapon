// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FindSessionsCallbackProxy.h"
#include "LobbyWidget.generated.h"

class UButton;
class UWrapBox;
class URoomWidget;
class UMakeRoomPopUpWidget;

UCLASS()
class PROJECT_GODOFWEAPON_API ULobbyWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	virtual bool Initialize() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> MakeRoomButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> SingleGameButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> RefreshButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UWrapBox> RoomWrapBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lobby")
	TSubclassOf<URoomWidget> SessionItemWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lobby")
	TSubclassOf<UMakeRoomPopUpWidget> MakeRoomPopUpWidgetClass;

	UFUNCTION(BlueprintCallable)
	void SetInfo();

	UFUNCTION(BlueprintCallable)
	void RefreshList();

protected:
	UPROPERTY(BlueprintReadWrite)
	TArray<TObjectPtr<URoomWidget>> SessionItemWidgets;

	UPROPERTY(BlueprintReadWrite)
	TArray<FBlueprintSessionResult> SessionResults;
};