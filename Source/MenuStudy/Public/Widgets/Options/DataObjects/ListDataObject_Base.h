// JSRS All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ListDataObject_Base.generated.h"

#define LIST_DATA_ACCESSOR(DataType,PropertyName) \
FORCEINLINE DataType Get##PropertyName() const { return PropertyName; } \
void Set##PropertyName(const DataType In##PropertyName) { PropertyName = In##PropertyName; }

/**
 * 
 */
UCLASS()
class MENUSTUDY_API UListDataObject_Base : public UObject
{
	GENERATED_BODY()

private:
	FName DataID;
	FText DataDisplayName;
	FText DescriptionRichText;
	FText DisabledRichText;
	TSoftObjectPtr<UTexture2D> SoftDescriptionImage;

	UPROPERTY(Transient)
	TObjectPtr<UListDataObject_Base> ParentData;

protected:

	//Empty in base class. Child classes should override it to handle the initialization needed accordingly
	virtual void OnDataObjectInitialized() {};
	
public:
	LIST_DATA_ACCESSOR(FName, DataID);
	LIST_DATA_ACCESSOR(FText, DataDisplayName);
	LIST_DATA_ACCESSOR(FText, DescriptionRichText);
	LIST_DATA_ACCESSOR(FText, DisabledRichText);
	LIST_DATA_ACCESSOR(TSoftObjectPtr<UTexture2D>, SoftDescriptionImage);
	
	FORCEINLINE UListDataObject_Base* GetParentData() const { return ParentData; }
	void SetParentData(UListDataObject_Base* InParentData) { ParentData = InParentData; };

	void InitDataObject();
	
	//Empty in the base classm Child class ListDataObject_Collection should override it. The function should return all the child data a tab has
	virtual TArray<UListDataObject_Base*> GetAllChildListData() const { return TArray<UListDataObject_Base*>(); }
	virtual bool HasAnyChildListData() const { return false; }
};
