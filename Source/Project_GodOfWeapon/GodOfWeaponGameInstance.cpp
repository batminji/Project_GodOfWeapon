// Fill out your copyright notice in the Description page of Project Settings.


#include "GodOfWeaponGameInstance.h"
#include "Engine/DataTable.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "Online/OnlineSessionNames.h"

void UGodOfWeaponGameInstance::Init()
{
	Super::Init();

	if (IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get())
	{
		SessionInterface = Subsystem->GetSessionInterface();
		if (SessionInterface)
		{
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UGodOfWeaponGameInstance::OnCreateSessionComplete);
			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UGodOfWeaponGameInstance::OnFindSessionsComplete);
		}
	}
}

void UGodOfWeaponGameInstance::UpdatePlayerCustomData(const FCustomData& InCustomData)
{
	PlayerCustomData = InCustomData;
}

void UGodOfWeaponGameInstance::CreateServerSession(FName SessionName, int32 MaxPlayers)
{
	if (!SessionInterface.IsValid()) return;

	auto ExistingSession = SessionInterface->GetNamedSession(NAME_GameSession);
	if (ExistingSession != nullptr)
	{
		SessionInterface->DestroySession(NAME_GameSession);
	}

	FOnlineSessionSettings SessionSettings;
	SessionSettings.bIsLANMatch = true;
	SessionSettings.NumPublicConnections = MaxPlayers;
	SessionSettings.bAllowJoinInProgress = true;
	SessionSettings.bAllowJoinViaPresence = true;
	SessionSettings.bShouldAdvertise = true;
	SessionSettings.bUsesPresence = true;

	SessionSettings.Set(FName("ROOM_NAME"), SessionName.ToString(), EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);

	UE_LOG(LogTemp, Log, TEXT("Creating session with name: %s, MaxPlayers: %d"), *SessionName.ToString(), MaxPlayers);
	SessionInterface->CreateSession(0, NAME_GameSession, SessionSettings);
}

void UGodOfWeaponGameInstance::FindServerSessions()
{
	UE_LOG(LogTemp, Log, TEXT("Finding sessions..."));

	if (!SessionInterface)
	{
		return;
	}

	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	SessionSearch->bIsLanQuery = true;
	SessionSearch->MaxSearchResults = 100;
	SessionSearch->QuerySettings.Set(SEARCH_LOBBIES, true, EOnlineComparisonOp::Equals);

	SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
}

void UGodOfWeaponGameInstance::OnCreateSessionComplete(FName SessionName, bool bSuccess)
{
	UE_LOG(LogTemp, Log, TEXT("OnCreateSessionComplete: SessionName: %s, bSuccess: %s"), *SessionName.ToString(), bSuccess ? TEXT("true") : TEXT("false"));

	if (bSuccess)
	{
		// GetWorld()->ServerTravel("/Game/Maps/RoomMap?listen");
	}
}

void UGodOfWeaponGameInstance::OnFindSessionsComplete(bool bSuccess)
{
	OnSessionSearchCompleted.Broadcast(bSuccess);
}

void UGodOfWeaponGameInstance::ExpandInventory()
{
	bool bRandom = FMath::RandBool();
	int32& Selected = bRandom ? InventoryColumns : InventoryRows;
	Selected++;
}
