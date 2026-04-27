// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseItemActor.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "../Player/InGamePlayer.h"
#include "../Monster/BaseMonster.h"

// Sets default values
ABaseItemActor::ABaseItemActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	RootComponent = ItemMesh;

	RangeSphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("RangeSphereCollision"));
	RangeSphereCollision->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABaseItemActor::BeginPlay()
{
	Super::BeginPlay();
	
	SetPlayer();
}

void ABaseItemActor::SetPlayer()
{
	InGamePlayer = Cast<AInGamePlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}

bool ABaseItemActor::IsCanAttack()
{
	if(ItemCurrentState == EItemState::Idle || bCanAttack)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool ABaseItemActor::IsMonsterInRange()
{
	TArray<AActor*> OverlappingActors;
	TSubclassOf<AActor> ClassFilter = ABaseMonster::StaticClass();
	RangeSphereCollision->GetOverlappingActors(OverlappingActors, ClassFilter);

	return OverlappingActors.Num() > 0;
}

// Called every frame
void ABaseItemActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (ItemCurrentState)
	{
		case EItemState::Idle:
			// Idle Event
			break;
	}
}

