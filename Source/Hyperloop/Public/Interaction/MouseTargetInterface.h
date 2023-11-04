// all rights reserved, Copyright Alleyne Technologies

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MouseTargetInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMouseTargetInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class HYPERLOOP_API IMouseTargetInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void HighLightActor() = 0;
	virtual void UnHighLightActor() = 0;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetCombatTarget(AActor* InCombatTarget);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	AActor* GetCombatTarget();

	
};
