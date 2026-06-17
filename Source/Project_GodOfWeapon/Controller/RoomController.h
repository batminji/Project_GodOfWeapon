// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "../Structs/PlayerStructs.h"
#include "../Enums/StageEnums.h"
#include "../Structs/ItemStructs.h"
#include "RoomController.generated.h"

class URoomHUDWidget;
class ARoomCharacter;

UCLASS()
class PROJECT_GODOFWEAPON_API ARoomController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ARoomController();

	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(Server, Reliable)
	void ServerSendCustomData(const FCustomData& InCustomData);

	void SetMyRoomCharacter(ARoomCharacter* InCharacter);

public:
	UFUNCTION(BlueprintCallable)
	void HandleEntry(const FSavedItemData& InItemData, EDifficulty InDifficulty);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<URoomHUDWidget> RoomHUDWidgetClass;

	void ShowRoomHUD();

	class AActor* GetCameraByTag(const FName& InTag);

private:
	UPROPERTY(ReplicatedUsing = OnRep_MyRoomCharacter)
	ARoomCharacter* MyRoomCharacter;

	UFUNCTION()
	void OnRep_MyRoomCharacter();

	void TrySendCustomData();

protected:
	UFUNCTION(Server, Reliable)
	void ServerStartGameWithData(const FSavedItemData& InItemData, EDifficulty InDifficulty);

	UFUNCTION(Client, Reliable)
	void ClientUpdateGameInstanceData(const FSavedItemData& InItemData, EDifficulty InDifficulty);

	void ExecuteServerTravel();
};
