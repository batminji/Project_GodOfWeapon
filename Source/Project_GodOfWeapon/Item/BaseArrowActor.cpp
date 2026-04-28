// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseArrowActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "NiagaraComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

ABaseArrowActor::ABaseArrowActor()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetBoxExtent(FVector(100.0f, 10.0f, 10.0f));
	RootComponent = BoxComponent;

	ArrowMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ArrowMeshComponent"));
	ArrowMeshComponent->SetupAttachment(BoxComponent);
	ArrowMeshComponent->SetWorldRotation(FRotator(-90.0f, 0.0f, 0.0f));

	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
	NiagaraComponent->SetupAttachment(BoxComponent);
	NiagaraComponent->SetWorldRotation(FRotator(0.0f, 180.0f, 0.0f));

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->InitialSpeed = 2000.0f;
	ProjectileMovementComponent->MaxSpeed = 2000.0f;
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
}

void ABaseArrowActor::BeginPlay()
{
	Super::BeginPlay();
	
	SetLifeSpan(5.0f);
	InitArrow(AttackDamage, InArrowStaticMesh, InArrowNiagaraSystem);
}

void ABaseArrowActor::InitArrow(float InAttackDamage, UStaticMesh* InArrowMesh, UNiagaraSystem* InArrowNiagara)
{
	AttackDamage = InAttackDamage;
	if (ArrowMeshComponent && InArrowMesh)
	{
		ArrowMeshComponent->SetStaticMesh(InArrowMesh);
	}
	if (NiagaraComponent && InArrowNiagara)
	{
		NiagaraComponent->SetAsset(InArrowNiagara);
	}
}

void ABaseArrowActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

