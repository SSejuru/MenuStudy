// JSRS All Rights Reserved


#include "Widgets/Widget_ActivatableBase.h"
#include "Controllers/MStudyPlayerController.h"

AMStudyPlayerController* UWidget_ActivatableBase::GetOwningCustomPlayerController()
{
	if(!CachedOwningPC.IsValid())
	{
		CachedOwningPC = GetOwningPlayer<AMStudyPlayerController>();
	}

	return CachedOwningPC.IsValid()? CachedOwningPC.Get() : nullptr;
}
