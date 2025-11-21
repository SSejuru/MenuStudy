// JSRS All Rights Reserved

#include "Subsystems/MStudyUISubsystem.h"
#include "Engine/AssetManager.h"
#include "MStudyDebugHelper.h"
#include "MStudyFunctionLibrary.h"
#include "Widgets/Widget_ActivatableBase.h"
#include "Widgets/Widget_PrimaryLayout.h"
#include "Widgets/CommonActivatableWidgetContainer.h"
#include "MStudyGameplayTags.h"
#include "Widgets/Widget_ConfirmScreen.h"

UMStudyUISubsystem* UMStudyUISubsystem::Get(const UObject* WorldContextObject)
{
	if (GEngine)
	{
		UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert);
		return UGameInstance::GetSubsystem<UMStudyUISubsystem>(World->GetGameInstance());
	}
	return nullptr;
}

bool UMStudyUISubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	if (!CastChecked<UGameInstance>(Outer)->IsDedicatedServerInstance())
	{
		TArray<UClass*> FoundClasses;
		GetDerivedClasses(GetClass(), FoundClasses);

		return FoundClasses.IsEmpty();
	}
	return false;
}

void UMStudyUISubsystem::RegisterPrimaryLayoutWidget(UWidget_PrimaryLayout* InCreatedWidget)
{
	check(InCreatedWidget);
	CreatedPrimaryLayout = InCreatedWidget;
	Debug::Print(TEXT("Primary layout widget assigned"));
}

void UMStudyUISubsystem::PushSoftWidgetToStackAsync(const FGameplayTag& InStackTag,
                                                    TSoftClassPtr<UWidget_ActivatableBase> InSoftWidgetClass,
                                                    TFunction<void(EAsyncPushWidgetState, UWidget_ActivatableBase*)> AsyncPushStateCallback)
{
	check(!InSoftWidgetClass.IsNull());

	UAssetManager::Get().GetStreamableManager().RequestAsyncLoad(
		InSoftWidgetClass.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda([InSoftWidgetClass, this, InStackTag, AsyncPushStateCallback]()
		{
			UClass* LoadedWidgetClass = InSoftWidgetClass.Get();
			check(LoadedWidgetClass && CreatedPrimaryLayout);

			UCommonActivatableWidgetContainerBase* WidgetStack = CreatedPrimaryLayout->GetWidgetStackByTag(InStackTag);

			UWidget_ActivatableBase* CreatedWidget = WidgetStack->AddWidget<UWidget_ActivatableBase>(
				LoadedWidgetClass,
				[AsyncPushStateCallback](UWidget_ActivatableBase& CreatedWidgetInstance)
				{
					AsyncPushStateCallback(EAsyncPushWidgetState::OnCreatedBeforePush, &CreatedWidgetInstance);
				}
			);

			AsyncPushStateCallback(EAsyncPushWidgetState::AfterPush, CreatedWidget);
		})
	);
}

void UMStudyUISubsystem::PushConfirmScreenToModalStackAsync(EConfirmScreenType InScreenType, const FText& InScreenTitle,
                                                            const FText& InScreenMessage, TFunction<void(EConfirmScreenButtonType)> ButtonClickedCallback)
{
	UConfirmScreenInfoObject* CreatedInfoObject = UConfirmScreenInfoObject::CreateConfirmScreenInfo(InScreenTitle, InScreenMessage, InScreenType);

	check(CreatedInfoObject);

	PushSoftWidgetToStackAsync(MStudyGameplayTags::UI_WidgetStack_Modal, UMStudyFunctionLibrary::GetUiSoftWidgetClassByTag(MStudyGameplayTags::UI_Widget_ConfirmScreen),
		[CreatedInfoObject, ButtonClickedCallback](EAsyncPushWidgetState InPushState, UWidget_ActivatableBase* PushedWidget)
		{
			if(InPushState == EAsyncPushWidgetState::OnCreatedBeforePush)
			{
				UWidget_ConfirmScreen* CreatedConfirmScreen = CastChecked<UWidget_ConfirmScreen>(PushedWidget);
				CreatedConfirmScreen->InitConfirmScreen(CreatedInfoObject, ButtonClickedCallback);
			}
		});
}
