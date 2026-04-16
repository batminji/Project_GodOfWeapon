// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseItemComponent.h"

UBaseItemComponent::UBaseItemComponent()
{
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
}
