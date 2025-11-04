// JSRS All Rights Reserved


#include "Widgets/Components/MStudyCommonButtonBase.h"
#include "CommonTextBlock.h"
#include "Subsystems/MStudyUISubsystem.h"

void UMStudyCommonButtonBase::SetButtonText(FText InText)
{
	if (CommonTextBlock_ButtonText && !InText.IsEmpty())
	{
		CommonTextBlock_ButtonText->SetText(bUseUpperCaseForButtonText ? InText.ToUpper() : InText);
	}
}

void UMStudyCommonButtonBase::NativePreConstruct()
{
	Super::NativePreConstruct();
	SetButtonText(ButtonDisplayText);
}

void UMStudyCommonButtonBase::NativeOnCurrentTextStyleChanged()
{
	Super::NativeOnCurrentTextStyleChanged();
	
	if (CommonTextBlock_ButtonText && GetCurrentTextStyleClass())
	{
		CommonTextBlock_ButtonText->SetStyle(GetCurrentTextStyleClass());
	}
}

void UMStudyCommonButtonBase::NativeOnHovered()
{
	Super::NativeOnHovered();
	if(ButtonDescriptionText.IsEmpty()) return;
	
	UMStudyUISubsystem::Get(this)->OnButtonDescriptionTextUpdated.Broadcast(this, ButtonDescriptionText);
}

void UMStudyCommonButtonBase::NativeOnUnhovered()
{
	Super::NativeOnUnhovered();
	if(ButtonDescriptionText.IsEmpty()) return;
	
	UMStudyUISubsystem::Get(this)->OnButtonDescriptionTextUpdated.Broadcast(this, FText::GetEmpty());
}
