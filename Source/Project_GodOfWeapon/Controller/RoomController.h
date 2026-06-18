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

	UFUNCTION(Server, Reliable, WithValidation)
	void C2S_SendCustomData(const FCustomData& InCustomData);
	bool C2S_SendCustomData_Validate(const FCustomData& InCustomData);
	void C2S_SendCustomData_Implementation(const FCustomData& InCustomData);

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
	UFUNCTION(Server, Reliable, WithValidation)
	void C2S_StartGameWithData(const FSavedItemData& InItemData, EDifficulty InDifficulty);
	bool C2S_StartGameWithData_Validate(const FSavedItemData& InItemData, EDifficulty InDifficulty);
	void C2S_StartGameWithData_Implementation(const FSavedItemData& InItemData, EDifficulty InDifficulty);

	UFUNCTION(Client, Reliable)
	void S2C_UpdateGameInstanceData(const FSavedItemData& InItemData, EDifficulty InDifficulty);
	void S2C_UpdateGameInstanceData_Implementation(const FSavedItemData& InItemData, EDifficulty InDifficulty);

	void ExecuteServerTravel();
};
