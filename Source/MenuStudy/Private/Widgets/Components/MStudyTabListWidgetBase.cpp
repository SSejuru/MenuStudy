// JSRS All Rights Reserved


#include "Widgets/Components/MStudyTabListWidgetBase.h"

#include "Editor/WidgetCompilerLog.h"
#include "Widgets/Components/MStudyCommonButtonBase.h"


void UMStudyTabListWidgetBase::RequestRegisterTab(const FName& InTabID, const FText& InTabDisplayName)
{
	RegisterTab(InTabID, TabButtonEntryWidgetClass, nullptr);

	if(UMStudyCommonButtonBase* TabButton = Cast<UMStudyCommonButtonBase>(GetTabButtonBaseByID(InTabID)))
	{
		TabButton->SetButtonText(InTabDisplayName);
	}
}

#if WITH_EDITOR
void UMStudyTabListWidgetBase::ValidateCompiledDefaults(class IWidgetCompilerLog& CompileLog) const
{
	Super::ValidateCompiledDefaults(CompileLog);

	if(!TabButtonEntryWidgetClass)
	{
		CompileLog.Error(FText::FromString(TEXT("The variable TabButtonEntryWidgetClass has no valid entry specified. ") +
			GetClass()->GetName() + TEXT(" needs a valid entry widget class to function properly")));
	}
}
#endif
