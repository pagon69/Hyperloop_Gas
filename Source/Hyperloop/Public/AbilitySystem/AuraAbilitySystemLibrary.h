// all rights reserved, Copyright Alleyne Technologies

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AuraAbilitySystemLibrary.generated.h"

class UAttributeMenuWidgetController;
class UOverlay_AuraWidgetController;

/**
 * 
 */
UCLASS()
class HYPERLOOP_API UAuraAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "AuraAbilitySystemLibrary|WidgetController") //static function to get the controller
	static UOverlay_AuraWidgetController* GetOverlayWidgetController(const UObject* WorldContextObject); 

	UFUNCTION(BlueprintPure, Category = "AuraAbilitySystemLibrary|WidgetController") //static function to get the controller for teh attribute menu
	static UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const UObject* WorldContextObject);
protected:


private:

	
};
