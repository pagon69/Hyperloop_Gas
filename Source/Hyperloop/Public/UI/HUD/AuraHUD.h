// all rights reserved, Copyright Alleyne Technologies

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AuraHUD.generated.h"

class UAttributeMenuWidgetController;
class UAttributeSet;
class UAbilitySystemComponent;
struct FWidgetControllerParams;
class UAuraUserWidget;
class UOverlay_AuraWidgetController;

/**
 * 
 */

UCLASS()
class HYPERLOOP_API AAuraHUD : public AHUD
{
	GENERATED_BODY()

public:

	

	UOverlay_AuraWidgetController* GetOverlayWidgetController (const FWidgetControllerParams& WcParams);

	UAttributeMenuWidgetController* GetAttributeMenuWidgetController (const FWidgetControllerParams& WcParams);
	
	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

	
	
	
protected:

	//removed begin play and moved to the InitOverlay function
//	virtual void BeginPlay() override;
	
private:

	UPROPERTY()
	TObjectPtr<UAuraUserWidget> OverlayWidget;
	
	UPROPERTY()
	TObjectPtr<UOverlay_AuraWidgetController> OverlayWidgetController;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAuraUserWidget> OverlayWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlay_AuraWidgetController> OverlayWidgetControllerClass;

	UPROPERTY()
	TObjectPtr<UAttributeMenuWidgetController> AttributeMenuWidgetController;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAttributeMenuWidgetController> AttributeMenuWidgetControllerClass; 
};
