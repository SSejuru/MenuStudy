// JSRS All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Widget_ActivatableBase.h"
#include  "FrontendTypes/FrontendEnumTypes.h"
#include "Widget_ConfirmScreen.generated.h"

class UDynamicEntryBox;
class UCommonTextBlock;

USTRUCT(BlueprintType)
struct FConfirmScreenButtonInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EConfirmScreenButtonType ButtonType = EConfirmScreenButtonType::Unknown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText ButtonTextToDisplay;
};

UCLASS()
class MENUSTUDY_API UConfirmScreenInfoObject : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(Transient)
	FText ScreenTitle;

	UPROPERTY(Transient)
	FText ScreenMessage;

	UPROPERTY(Transient)
	TArray<FConfirmScreenButtonInfo> AvailableScreenButtons;

	static UConfirmScreenInfoObject* CreateConfirmScreenInfo(const FText& InScreenTitle, const FText& InScreenMessage, const EConfirmScreenType& InConfirmScreenType);
};

/**
 * 
 */
UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class MENUSTUDY_API UWidget_ConfirmScreen : public UWidget_ActivatableBase
{
	GENERATED_BODY()

public:
	
	//Gets Called outside of the class when the widget is constructed and before its pushed to the stack
	void InitConfirmScreen(const UConfirmScreenInfoObject* InScreenInfoObject, TFunction<void(EConfirmScreenButtonType)> ClickedButtonCallback);
	
private:

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonTextBlock> CommonTextBlock_Title;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonTextBlock> CommonTextBlock_Message;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UDynamicEntryBox> DynamicEntryBox_Buttons;
};
