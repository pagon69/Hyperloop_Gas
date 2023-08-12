// all rights reserved, Copyright Alleyne Technologies

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "EveUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class HYPERLOOP_API UEveUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;

	
	
protected:

	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();
	
};
