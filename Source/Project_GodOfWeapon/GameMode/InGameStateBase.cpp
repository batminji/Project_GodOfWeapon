// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameStateBase.h"
#include "Net/UnrealNetwork.h"

void AInGameStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AInGameStateBase, CurrentStage);
    DOREPLIFETIME(AInGameStateBase, LevelMultiplier);
    DOREPLIFETIME(AInGameStateBase, CurrentAliveMonsterCount);
}

void AInGameStateBase::OnReplicate_CurrentStage()
{
}
