// JSRS All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Widget_ActivatableBase.h"
#include "Widget_OptionsScreen.generated.h"

class UMStudyTabListWidgetBase;
class UOptionsDataRegistry;
/**
 * 
 */
UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class MENUSTUDY_API UWidget_OptionsScreen : public UWidget_ActivatableBase
{
	GENERATED_BODY()

protected:
	//~ Begin UUSerWidgetInterface
	virtual void NativeOnInitialized() override;
	//~ End UUSerWidgetInterface

	//~ Begin UCommonActivatableWidget Interface
	virtual void NativeOnActivated() override;
	//~ End UCommonActivatableWidget Interface
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Frontend Options Screen", meta = (RowType = "/Script/CommonUI.CommonInputActionDataBase"))
	FDataTableRowHandle ResetAction;

	FUIActionBindingHandle ResetActionHandle;

	//Handle the creation of Data in options Screen. Direct access to this variable is forbidden
	UPROPERTY(Transient)
	TObjectPtr<UOptionsDataRegistry> OwningDataRegistry;

	//**** Bound Widgets ****//
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UMStudyTabListWidgetBase> TabListWidget_OptionsTabs;
	//**** Bound Widgets ****//

	void OnResetBoundActionTriggered();
	void OnBackBoundActionTriggered();

	UFUNCTION()
	void OnOptionsTabSelected(FName TabID);

public:
	UOptionsDataRegistry* GetDataRegistry();
	
};
