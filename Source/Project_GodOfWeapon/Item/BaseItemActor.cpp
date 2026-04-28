// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseItemActor.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "NiagaraComponent.h"
#include "Engine/OverlapResult.h"
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
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_GameTraceChannel2);

	return GetWorld()->OverlapAnyTestByObjectType(GetActorLocation(),FQuat::Identity,ObjectQueryParams,FCollisionShape::MakeSphere(ItemStat.AttackRange),FCollisionQueryParams::DefaultQueryParam);
}

void ABaseItemActor::FindTargetInRange(AActor*& OutTargetActor, FVector& OutTargetLocation)
{
	float NearestLength = TNumericLimits<float>::Max();
	OutTargetActor = nullptr;
	OutTargetLocation = FVector::ZeroVector;

	TArray<FOverlapResult> OverlappingResults;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);
	if (InGamePlayer)
	{
		CollisionParams.AddIgnoredActor(InGamePlayer);
	}

	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_GameTraceChannel2);

	GetWorld()->OverlapMultiByObjectType(OverlappingResults,GetActorLocation(),FQuat::Identity,ObjectQueryParams,FCollisionShape::MakeSphere(ItemStat.AttackRange),CollisionParams);

	AActor* NearestTargetRef = nullptr;

	for (const FOverlapResult& Result : OverlappingResults)
	{
		if (AActor* HitActor = Result.GetActor())
		{
			float DistanceSquared = FVector::DistSquared(GetActorLocation(), HitActor->GetActorLocation());

			if (DistanceSquared < NearestLength)
			{
				NearestLength = DistanceSquared;
				NearestTargetRef = HitActor;
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

