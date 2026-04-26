// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameController.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

void AInGameController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

    if (IsLocalPlayerController())
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
    }

	SetInputMode(FInputModeGameOnly());
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
