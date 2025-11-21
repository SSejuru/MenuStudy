// JSRS All Rights Reserved


#include "AsyncActions/AsyncAction_PushConfirmScreen.h"

#include "Subsystems/MStudyUISubsystem.h"

UAsyncAction_PushConfirmScreen* UAsyncAction_PushConfirmScreen::PushConfirmScreen(const UObject* WorldContextObject, EConfirmScreenType InConfirmScreenType,
                                                                                  FText InScreenTitle, FText InScreenMessage)
{
	if(GEngine)
	{
		if(UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
		{
			UAsyncAction_PushConfirmScreen* Node = NewObject<UAsyncAction_PushConfirmScreen>();
			Node->CachedOwningWorld = World;
			Node->CachedScreenType = InConfirmScreenType;
			Node->CachedScreenTitle = InScreenTitle;
			Node->CachedScreenMessage = InScreenMessage;

			Node->RegisterWithGameInstance(World);
			
			return Node;
		}
	}

	return nullptr;
}

void UAsyncAction_PushConfirmScreen::Activate()
{
	Super::Activate();

	UMStudyUISubsystem* UISubsystem = UMStudyUISubsystem::Get(CachedOwningWorld.Get());
	UISubsystem->PushConfirmScreenToModalStackAsync(CachedScreenType, CachedScreenTitle, CachedScreenMessage,
		[this](EConfirmScreenButtonType ButtonClickedCallback)
		{
			OnButtonClicked.Broadcast(ButtonClickedCallback);
			SetReadyToDestroy();
		});
}
