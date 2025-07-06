// JSRS All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MStudyFunctionLibrary.generated.h"

class UWidget_ActivatableBase;
/**
 * 
 */
UCLASS()
class MENUSTUDY_API UMStudyFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category = "MStudy Function Library")
	static TSoftClassPtr<UWidget_ActivatableBase> GetUiSoftWidgetClassByTag(UPARAM(meta = (Categories = "UI.Widget"))FGameplayTag InWidgetTag);
};
