// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseItemActor.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "NiagaraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/ChildActorComponent.h"
#include "../Player/InGamePlayer.h"
#include "../Monster/BaseMonster.h"
#include "../Structs/PlayerStructs.h"

ABaseItemActor::ABaseItemActor()
{
	PrimaryActorTick.bCanEverTick = true;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	RootComponent = ItemMesh;

	Niagara = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara"));
	Niagara->SetupAttachment(ItemMesh);

	RangeSphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("RangeSphereCollision"));
	RangeSphereCollision->SetupAttachment(RootComponent);
}

void ABaseItemActor::BeginPlay()
{
	Super::BeginPlay();
	
	SetPlayer();
}

void ABaseItemActor::InitItem(EItemType InItemType, FItemStat InItemStat, USpringArmComponent* InOwnerSpringArm, UChildActorComponent* InOwnerChildActorComponent, UStaticMesh* InItemMesh, UNiagaraSystem* InItemNiagara, UStaticMesh* InArrowMesh, UNiagaraSystem* InArrowNiagara)
{
	ItemType = InItemType;
	if(ItemType == EItemType::Bow)
	{
		UpdateLongRangeItemStat(InItemStat);
	}
	else
	{
		UpdateShortRangeItemStat(InItemStat);
	}

	OwnerSpringArm = InOwnerSpringArm;
	OwnerChildActor = InOwnerChildActorComponent;

	if (ItemMesh && InItemMesh)
	{
		ItemMesh->SetStaticMesh(InItemMesh);
	}
	if (Niagara && InItemNiagara)
	{
		Niagara->SetAsset(InItemNiagara);
	}
	if (InArrowMesh)
	{
		ArrowStaticMesh = InArrowMesh;
	}
	if (InArrowNiagara)
	{
		ArrowNiagaraSystem = InArrowNiagara;
	}

	if (RangeSphereCollision)
	{
		RangeSphereCollision->SetSphereRadius(ItemStat.AttackRange);
	}
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
	RangeSphereCollision->GetOverlappingActors(OverlappingActors, ABaseMonster::StaticClass());

	return OverlappingActors.Num() > 0;
}

void ABaseItemActor::FindTargetInRange(AActor*& OutTargetActor, FVector& OutTargetLocation)
{
	float NearestLength = TNumericLimits<float>::Max();
	OutTargetActor = nullptr;
	OutTargetLocation = FVector::ZeroVector;

	TArray<AActor*> OverlappingActors;
	RangeSphereCollision->GetOverlappingActors(OverlappingActors, ABaseMonster::StaticClass());

	AActor* NearestTargetRef = nullptr;

	for (AActor* Actor : OverlappingActors)
	{
		if (Actor)
		{
			float Distance = GetDistanceTo(Actor);
			if (Distance < NearestLength)
			{
				NearestLength = Distance;
				NearestTargetRef = Actor;
			}
		}
	}

	if (NearestTargetRef)
	{
		OutTargetActor = NearestTargetRef;
		OutTargetLocation = NearestTargetRef->GetActorLocation();
	}
}

void ABaseItemActor::UpdateShortRangeItemStat(FItemStat InStat)
{
	if (InGamePlayer)
	{
		ItemStat.Damage = InStat.Damage * InGamePlayer->GetCurrentPlayerStat().ShortRangeAttackForce;
		ItemStat.AttackRange = InStat.AttackRange * InGamePlayer->GetCurrentPlayerStat().AttackRangeMultifier;
		ItemStat.AttackSpeed = InStat.AttackSpeed * InGamePlayer->GetCurrentPlayerStat().AttackSpeedMultifier;
		ItemStat.CooldownTime = InStat.CooldownTime;
	}
}

void ABaseItemActor::UpdateLongRangeItemStat(FItemStat InStat)
{
	if (InGamePlayer)
	{
		ItemStat.Damage = InStat.Damage * InGamePlayer->GetCurrentPlayerStat().LongRangeAttackForce;
		ItemStat.AttackRange = InStat.AttackRange * InGamePlayer->GetCurrentPlayerStat().AttackRangeMultifier;
		ItemStat.AttackSpeed = InStat.AttackSpeed * InGamePlayer->GetCurrentPlayerStat().AttackSpeedMultifier;
		ItemStat.CooldownTime = InStat.CooldownTime;
	}
}

void ABaseItemActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (ItemCurrentState)
	{
	case EItemState::Idle:
		{
		Idle();
			break;
		}
	default:
		{
			break;
		}
	}
}

