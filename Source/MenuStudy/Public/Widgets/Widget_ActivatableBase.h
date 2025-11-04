// JSRS All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "Widget_ActivatableBase.generated.h"

class AMStudyPlayerController;
/**
 * 
 */
UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class MENUSTUDY_API UWidget_ActivatableBase : public UCommonActivatableWidget
{
	GENERATED_BODY()

private:
	TWeakObjectPtr<AMStudyPlayerController> CachedOwningPC;

protected:

	UFUNCTION(BlueprintPure)
	AMStudyPlayerController* GetOwningCustomPlayerController();
	
};
