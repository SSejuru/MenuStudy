// JSRS All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "CommonTabListWidgetBase.h"
#include "MStudyTabListWidgetBase.generated.h"

class UMStudyCommonButtonBase;
/**
 * 
 */
UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class MENUSTUDY_API UMStudyTabListWidgetBase : public UCommonTabListWidgetBase
{
	GENERATED_BODY()

public:

	void RequestRegisterTab(const FName& InTabID, const FText& InTabDisplayName);
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Frontend Tab List Settings", meta = (AllowPrivateAccess = "true", ClampMin = "1", ClampMax = "10"))
	int32 DebugEditorPreviewTabCount = 3;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Frontend Tab List Settings", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UMStudyCommonButtonBase> TabButtonEntryWidgetClass;

	//~ Begin UWidget Interface
#if WITH_EDITOR	
	virtual void ValidateCompiledDefaults(class IWidgetCompilerLog& CompileLog) const override;
#endif
	//~ End UWidget Interface
};
