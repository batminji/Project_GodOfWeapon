// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameController.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Blueprint/UserWidget.h"
#include "../GodOfWeaponGameInstance.h"
#include "../Player/PlayerStateBase.h"
#include "../GameMode/InGameMode.h"

void AInGameController::BeginPlay()
{
	Super::BeginPlay();

    if(!IsLocalPlayerController())
    {
        return;
	}   
    ShowInGameMainWidget();
    SetupInputMappingContext();

    if (UGodOfWeaponGameInstance* GameInstance = Cast<UGodOfWeaponGameInstance>(GetGameInstance()))
    {
        C2S_RequestLoadPlayerState(GameInstance->SavedPlayerStat, GameInstance->SavedPlayerGold);
    }
}

void AInGameController::C2S_RequestLoadPlayerState_Implementation(FPlayerStatStructure InPlayerStat, int32 InPlayerCoin)
{
    APlayerStateBase* MyPlayerState = GetPlayerState<APlayerStateBase>();
    if (MyPlayerState)
    {
        MyPlayerState->Server_UpdateStat(InPlayerStat);
        MyPlayerState->Server_UpdateCoin(InPlayerCoin);
    }
}

bool AInGameController::C2S_RequestLoadPlayerState_Validate(FPlayerStatStructure InPlayerStat, int32 InPlayerCoin)
{
    return true;
}

void AInGameController::S2C_SavePlayerStateToInstance_Implementation()
{
    if (!IsLocalController())
    {
        return;
    }

    UGodOfWeaponGameInstance* GameInstance = Cast<UGodOfWeaponGameInstance>(GetGameInstance());
    APlayerStateBase* MyPlayerState = GetPlayerState<APlayerStateBase>();

    if (GameInstance && MyPlayerState)
    {
        GameInstance->SavedPlayerStat = MyPlayerState->GetPlayerStat();
        GameInstance->SavedPlayerGold = MyPlayerState->GetPlayerCoin();
    }

    C2S_NotifySaveFinished();
}

void AInGameController::C2S_NotifySaveFinished_Implementation()
{
    if (HasAuthority())
    {
        if (AInGameMode* GameMode = Cast<AInGameMode>(GetWorld()->GetAuthGameMode()))
        {
            GameMode->OnPlayerSaveCompleted(this);
        }
    }
}

bool AInGameController::C2S_NotifySaveFinished_Validate()
{
    return true;
}

void AInGameController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void AInGameController::OnUnPossess()
{
	Super::OnUnPossess();

    if (IsLocalPlayerController())
    {
        UEnhancedInputLocalPlayerSubsystem* Subsystem =
            ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
        if (Subsystem)
        {
            Subsystem->ClearAllMappings();
        }
    }
}

void AInGameController::SetupInputMappingContext()
{
    UEnhancedInputLocalPlayerSubsystem* Subsystem =
    ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
    if (Subsystem)
    {
        Subsystem->ClearAllMappings();
        if (!InputMappingContext.IsNull())
        {
            UInputMappingContext* LoadedIMC = InputMappingContext.LoadSynchronous();
            if (LoadedIMC)
            {
                Subsystem->AddMappingContext(LoadedIMC, 0);
            }
        }
    }

    SetInputMode(FInputModeGameOnly());
}

void AInGameController::ShowInGameMainWidget()
{
    if (InGameMainWidgetClass)
    {
        InGameMainWidget = CreateWidget<UUserWidget>(GetWorld(), InGameMainWidgetClass);
        if (InGameMainWidget)
        {
            InGameMainWidget->AddToViewport();
			SetInputMode(FInputModeGameAndUI());
            SetShowMouseCursor(true);
        }
    }
}
