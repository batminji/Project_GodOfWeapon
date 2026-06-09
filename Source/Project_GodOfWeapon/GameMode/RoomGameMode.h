// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RoomGameMode.generated.h"

class ARoomCharacter;

UCLASS()
class PROJECT_GODOFWEAPON_API ARoomGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void PostLogin(APlayerController* NewPlayer) override;

	AActor* FindSpawnSpotByTag(const FName& InTag);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Player")
	TSubclassOf<ARoomCharacter> RoomCharacterClass;
};
