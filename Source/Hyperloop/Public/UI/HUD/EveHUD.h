// all rights reserved, Copyright Alleyne Technologies

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "EveHUD.generated.h"

class UEveUserWidget;

/**
 * 
 */
UCLASS()
class HYPERLOOP_API AEveHUD : public AHUD
{
	GENERATED_BODY()

public:
	
	UPROPERTY()
	TObjectPtr<UEveUserWidget> OverlayWidget;


protected:

	virtual void BeginPlay() override;
	
private:
	//TODO: do i need to change the widget from aura to eve ?
	UPROPERTY(EditAnywhere)
	TSubclassOf<UEveUserWidget> OverlayWidgetClass;
	
	
};
