// Fill out your copyright notice in the Description page of Project Settings.


#include "MakeRoomPopUpWidget.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "../../GodOfWeaponGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UMakeRoomPopUpWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

//void UMakeRoomPopUpWidget::OnCancleButtonClicked()
//{
//	RemoveFromParent();
//}
//
//void UMakeRoomPopUpWidget::OnConfirmButtonClicked()
//{
//	FName RoomName = FName(*RoomNameEditableText->GetText().ToString());
//
//	int32 MaxPlayers = FCString::Atoi(*NumOfPeopleEditableText->GetText().ToString());
//
//	UGodOfWeaponGameInstance* GameInstance = Cast<UGodOfWeaponGameInstance>(GetGameInstance());
//	if (GameInstance)
//	{
//		GameInstance->CreateServerSession(RoomName, MaxPlayers);
//	}
//
//	// RemoveFromParent();
//}
//
//void UMakeRoomPopUpWidget::OnSessionCreateCompleted(bool bSuccess)
//{
//	RemoveFromParent();
//
//	if (bSuccess)
//	{
//		RemoveFromParent();
//
//		UGameplayStatics::OpenLevel(GetWorld(), FName("RoomMap"), true, TEXT("listen"));
//	}
//	else
//	{
//		UE_LOG(LogTemp, Error, TEXT("Create Room Fail"));
//	}
//}
