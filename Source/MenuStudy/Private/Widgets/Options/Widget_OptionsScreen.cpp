// JSRS All Rights Reserved


#include "Widgets/Options/Widget_OptionsScreen.h"

#include "ICommonInputModule.h"
#include "MStudyDebugHelper.h"
#include "Input/CommonUIInputTypes.h"
#include "Widgets/Components/MStudyTabListWidgetBase.h"
#include "Widgets/Options/OptionsDataRegistry.h"
#include "Widgets/Options/DataObjects/ListDataObject_Collection.h"

void UWidget_OptionsScreen::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if(!ResetAction.IsNull())
	{
		ResetActionHandle = RegisterUIActionBinding(FBindUIActionArgs(ResetAction, true, 
	FSimpleDelegate::CreateUObject(this, &ThisClass::OnResetBoundActionTriggered)));
	}

	RegisterUIActionBinding(FBindUIActionArgs(ICommonInputModule::GetSettings().GetDefaultBackAction(), true,
		FSimpleDelegate::CreateUObject(this, &ThisClass::OnBackBoundActionTriggered)));

	TabListWidget_OptionsTabs->OnTabSelected.AddUniqueDynamic(this, &ThisClass::OnOptionsTabSelected);
}

void UWidget_OptionsScreen::NativeOnActivated()
{
	Super::NativeOnActivated();

	for(auto TabCollection : GetDataRegistry()->GetRegisteredOptionsTabCollections())
	{
		if(!TabCollection)
			continue;

		const FName TabID = TabCollection->GetDataID();
		if(TabListWidget_OptionsTabs->GetTabButtonBaseByID(TabID))
		{
			continue;
		}

		TabListWidget_OptionsTabs->RequestRegisterTab(TabID, TabCollection->GetDataDisplayName());
	}
}

void UWidget_OptionsScreen::OnResetBoundActionTriggered()
{
	Debug::Print("Reset Bound action triggered");
}

void UWidget_OptionsScreen::OnBackBoundActionTriggered()
{
	DeactivateWidget();
}

void UWidget_OptionsScreen::OnOptionsTabSelected(FName TabID)
{
	Debug::Print(TEXT("Tab Selected: ") + TabID.ToString());
}

UOptionsDataRegistry* UWidget_OptionsScreen::GetDataRegistry()
{
	if(!OwningDataRegistry)
	{
		OwningDataRegistry = NewObject<UOptionsDataRegistry>();
		OwningDataRegistry->InitOptionsDataRegistry(GetOwningLocalPlayer());
	}
	checkf(OwningDataRegistry, TEXT("Data registry for options screen is not valid"));
	return OwningDataRegistry;
}

