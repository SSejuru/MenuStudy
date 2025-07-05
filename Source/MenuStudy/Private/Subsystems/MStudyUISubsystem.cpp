// JSRS All Rights Reserved

#include "Subsystems/MStudyUISubsystem.h"
#include "Engine/AssetManager.h"
#include "MStudyDebugHelper.h"
#include "Widgets/Widget_ActivatableBase.h"
#include "Widgets/Widget_PrimaryLayout.h"
#include "Widgets/CommonActivatableWidgetContainer.h"

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
