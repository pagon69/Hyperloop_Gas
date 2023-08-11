// all rights reserved, Copyright Alleyne Technologies

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "EveHUD.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;
struct FWidgetControllerParameters;
class UEveUserWidget;
class UOverlay_EveWidgetController;
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

	UOverlay_EveWidgetController* GetOverlayWidgetController (const FWidgetControllerParameters& WcParams);

	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);
	
protected:

//	virtual void BeginPlay() override;
	
private:
	//TODO: do i need to change the widget from aura to eve ?
	UPROPERTY(EditAnywhere)
	TSubclassOf<UEveUserWidget> OverlayWidgetClass;
	
	UPROPERTY()
	TObjectPtr<UOverlay_EveWidgetController> OverlayWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlay_EveWidgetController> OverlayWidgetControllerClass;
};
