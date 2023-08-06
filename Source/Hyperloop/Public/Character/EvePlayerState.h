// all rights reserved, Copyright Alleyne Technologies

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "EvePlayerState.generated.h"


class UAbilitySystemComponent;
class UAttributeSet;

/**
 * 
 */
UCLASS()
class HYPERLOOP_API AEvePlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AEvePlayerState();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override; //system required getter for ability system componenbt

	UAttributeSet* GetAttributeSet() const { return AttributeSet; } // getter for the attribute set

protected:

	//attribute set and ability system - not full built out
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
	
};
