// JSRS All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MStudyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MENUSTUDY_API AMStudyPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:

	//~ Begin APlayerController Interface
	virtual void OnPossess(APawn* InPawn) override;
	//~ End APlayerController Interface

};
