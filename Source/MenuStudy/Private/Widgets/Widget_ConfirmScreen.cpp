// JSRS All Rights Reserved


#include "Widgets/Widget_ConfirmScreen.h"

#include "CommonTextBlock.h"
#include "ICommonInputModule.h"
#include "Components/DynamicEntryBox.h"
#include "Widgets/Components/MStudyCommonButtonBase.h"

UConfirmScreenInfoObject* UConfirmScreenInfoObject::CreateConfirmScreenInfo(
	const FText& InScreenTitle, const FText& InScreenMessage,
	const EConfirmScreenType& InConfirmScreenType)
{
	//Create Info Object
	UConfirmScreenInfoObject* InfoObject = NewObject<UConfirmScreenInfoObject>();
	InfoObject->ScreenTitle = InScreenTitle;
	InfoObject->ScreenMessage = InScreenMessage;

	//Create Buttons for screen
	switch (InConfirmScreenType)
	{
	case EConfirmScreenType::Ok:
		{
			FConfirmScreenButtonInfo OkButtonInfo;

			OkButtonInfo.ButtonType = EConfirmScreenButtonType::Close;
			OkButtonInfo.ButtonTextToDisplay = FText::FromString("Ok");

			InfoObject->AvailableScreenButtons.Add(OkButtonInfo);
			break;
		}

	case EConfirmScreenType::YesNo:
	case EConfirmScreenType::OkCancel:
		{
			FConfirmScreenButtonInfo ConfirmButtonInfo;
			FConfirmScreenButtonInfo CancelButtonInfo;

			ConfirmButtonInfo.ButtonType = EConfirmScreenButtonType::Confirm;
			CancelButtonInfo.ButtonType = EConfirmScreenButtonType::Cancel;

			ConfirmButtonInfo.ButtonTextToDisplay = FText::FromString(
				InConfirmScreenType == EConfirmScreenType::OkCancel ? "Ok" : "Yes");
			CancelButtonInfo.ButtonTextToDisplay = FText::FromString(
				InConfirmScreenType == EConfirmScreenType::OkCancel ? "Cancel" : "No");

			InfoObject->AvailableScreenButtons.Add(ConfirmButtonInfo);
			InfoObject->AvailableScreenButtons.Add(CancelButtonInfo);
			break;
		}
	default: 
		break;
	}

	return InfoObject;
}

void UWidget_ConfirmScreen::InitConfirmScreen(const UConfirmScreenInfoObject* InScreenInfoObject,
                                              TFunction<void(EConfirmScreenButtonType)> ClickedButtonCallback)
{
	check(InScreenInfoObject && CommonTextBlock_Title && CommonTextBlock_Message && DynamicEntryBox_Buttons);

	CommonTextBlock_Title->SetText(InScreenInfoObject->ScreenTitle);
	CommonTextBlock_Message->SetText(InScreenInfoObject->ScreenMessage);

	//Check if entry box has old buttons created previously
	if (DynamicEntryBox_Buttons->GetNumEntries() != 0)
	{
		//Clearing the old buttons, the widget type for the entry box is specified in the child WBP
		DynamicEntryBox_Buttons->Reset<UMStudyCommonButtonBase>(
			[](UMStudyCommonButtonBase& ExistingButton)
			{
				ExistingButton.OnClicked().Clear();
			}
		);
	}

	check(!InScreenInfoObject->AvailableScreenButtons.IsEmpty());

	for (const auto& AvailableButtonInfo : InScreenInfoObject->AvailableScreenButtons)
	{
		FDataTableRowHandle InputActionRowHandle;

		switch (AvailableButtonInfo.ButtonType)
		{
		case EConfirmScreenButtonType::Cancel:
		case EConfirmScreenButtonType::Close:
			InputActionRowHandle = ICommonInputModule::GetSettings().GetDefaultBackAction();
			break;
		default: 
			break;
		}

		UMStudyCommonButtonBase* AddedButton = DynamicEntryBox_Buttons->CreateEntry<UMStudyCommonButtonBase>();
		AddedButton->SetButtonText(AvailableButtonInfo.ButtonTextToDisplay);
		AddedButton->SetTriggeringInputAction(InputActionRowHandle);
		AddedButton->OnClicked().AddLambda(
			[ClickedButtonCallback, AvailableButtonInfo, this]()
			{
				ClickedButtonCallback(AvailableButtonInfo.ButtonType);
				DeactivateWidget();
			});
	}

	if(DynamicEntryBox_Buttons->GetNumEntries() != 0)
	{
		//Set focus on the last button.
		DynamicEntryBox_Buttons->GetAllEntries().Last()->SetFocus();
	}
}
