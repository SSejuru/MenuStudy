// JSRS All Rights Reserved


#include "Widgets/Options/DataObjects/ListDataObject_Collection.h"

TArray<UListDataObject_Base*> UListDataObject_Collection::GetAllChildListData() const
{
	return ChildListDataArray;
}

bool UListDataObject_Collection::HasAnyChildListData() const
{
	return !ChildListDataArray.IsEmpty();
}

void UListDataObject_Collection::AddChildListData(UListDataObject_Base* InChildListData)
{
	//Initialize data and set parent
	InChildListData->InitDataObject();
	InChildListData->SetParentData(this);

	//Add to list
	ChildListDataArray.Add(InChildListData);
}
