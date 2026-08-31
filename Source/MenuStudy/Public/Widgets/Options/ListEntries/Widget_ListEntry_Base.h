// JSRS All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Widget_ListEntry_Base.generated.h"

class UCommonTextBlock;
/**
 * 
 */
UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class MENUSTUDY_API UWidget_ListEntry_Base : public UCommonUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

protected:
	//~Begin IUserObjectListEntry
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	//~End IUserObjectListEntry

private:
	//**** Bound Widgets ****//
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true, BindWidgetOptional))
	TObjectPtr<UCommonTextBlock> CommonText_SettingDisplayName;
	//**** Bound Widgets ****//
};
