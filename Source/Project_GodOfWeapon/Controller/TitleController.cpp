// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleController.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraActor.h"
#include "TimerManager.h"

void ATitleController::BeginPlay()
{
	Super::BeginPlay();

	AActor* TitleCamera = GetCameraByTag(TEXT("TitleCamera"));
	if (TitleCamera)
	{
		SetViewTarget(TitleCamera);
	}

	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;
}

void ATitleController::MoveCamera()
{
	AActor* CustomCamera = GetCameraByTag(TEXT("CustomCamera"));
	if (CustomCamera)
	{
		SetViewTargetWithBlend(CustomCamera, 2.0f, VTBlend_EaseInOut, 2.0f);
	}

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ATitleController::OnTimerDelayEnded, 2.0f, false);
}

void ATitleController::CallCameraMoveFinished()
{
	if(OnCameraMoveFinished.IsBound())
	{
		OnCameraMoveFinished.Broadcast();
	}
}

AActor* ATitleController::GetCameraByTag(const FName& InTag)
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACameraActor::StaticClass(), FoundActors);

	for (AActor* Actor : FoundActors)
	{
		if (Actor->ActorHasTag(InTag))
		{
			return Actor;
		}
	}

	return nullptr;
}

void ATitleController::OnTimerDelayEnded()
{
	CallCameraMoveFinished();
}
