// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomGameMode.h"
#include "GameFramework/GameStateBase.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "../Player/RoomCharacter.h"

void ARoomGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (!GameState || !RoomCharacterClass)
	{
		return;
	}

	int32 PlayerIndex = GameState->PlayerArray.Num() - 1;
	FName SpotTag = FName(*FString::Printf(TEXT("Spot_%d"), PlayerIndex));

	AActor* SpawnSpot = FindSpawnSpotByTag(SpotTag);
	if (SpawnSpot)
	{
		FVector SpawnLocation = SpawnSpot->GetActorLocation();
		FRotator SpawnRotation = SpawnSpot->GetActorRotation();

		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = NewPlayer;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		ARoomCharacter* NewRoomCharacter = GetWorld()->SpawnActor<ARoomCharacter>(RoomCharacterClass, SpawnLocation, SpawnRotation, SpawnParams);
		if(NewRoomCharacter)
		{
			NewPlayer->Possess(NewRoomCharacter);
		}
	}
}

AActor* ARoomGameMode::FindSpawnSpotByTag(const FName& InTag)
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), FoundActors);
	for (AActor* Actor : FoundActors)
	{
		if (Actor->ActorHasTag(InTag)) return Actor;
	}
	return nullptr;
}