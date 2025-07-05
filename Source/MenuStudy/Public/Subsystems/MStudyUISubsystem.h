// JSRS All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Widgets/Widget_ActivatableBase.h"
#include "MStudyUISubsystem.generated.h"

class UWidget_ActivatableBase;
class UWidget_PrimaryLayout;
struct FGameplayTag;

enum class EAsyncPushWidgetState : uint8
{
	OnCreatedBeforePush,
	AfterPush
};

/**
 * 
 */
UCLASS()
class MENUSTUDY_API UMStudyUISubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	static UMStudyUISubsystem* Get(const UObject* WorldContextObject);

	//~Begin USubsystem Interface
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	//~End USubsystem Interface

	UFUNCTION(BlueprintCallable)
	void RegisterPrimaryLayoutWidget(UWidget_PrimaryLayout* InCreatedWidget);

	void PushSoftWidgetToStackAsync(const FGameplayTag& InStackTag, TSoftClassPtr<UWidget_ActivatableBase> InSoftWidgetClass,
									TFunction<void(EAsyncPushWidgetState, UWidget_ActivatableBase*)> AsyncPushStateCallback);
	
private:
	UPROPERTY(Transient)
	UWidget_PrimaryLayout* CreatedPrimaryLayout;
};
