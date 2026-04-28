// Fill out your copyright notice in the Description page of Project Settings.


#include "CoinActor.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "../Player/InGamePlayer.h"

ACoinActor::ACoinActor()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetBoxExtent(FVector(32.0f, 32.0f, 32.0f));
	RootComponent = BoxComponent;

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	WidgetComponent->SetupAttachment(BoxComponent);
}

void ACoinActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACoinActor::Init()
{
	SpawnLocation = GetActorLocation();

	InGamePlayer = Cast<AInGamePlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}

void ACoinActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

