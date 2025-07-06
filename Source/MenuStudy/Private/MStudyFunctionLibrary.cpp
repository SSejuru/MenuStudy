// JSRS All Rights Reserved


#include "MStudyFunctionLibrary.h"
#include "MStudySettings/MStudyDeveloperSettings.h"

TSoftClassPtr<UWidget_ActivatableBase> UMStudyFunctionLibrary::GetUiSoftWidgetClassByTag(UPARAM(meta = (Categories = "UI.Widget"))FGameplayTag InWidgetTag)
{
	const UMStudyDeveloperSettings* DeveloperSettings = GetDefault<UMStudyDeveloperSettings>();

	checkf(DeveloperSettings->WidgetsClassMap.Contains(InWidgetTag), TEXT("Could not find the corresponding widget for tag: %s"), *InWidgetTag.ToString());

	return DeveloperSettings->WidgetsClassMap.FindRef(InWidgetTag);
}
