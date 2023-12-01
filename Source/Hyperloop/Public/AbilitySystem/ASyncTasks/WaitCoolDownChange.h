// all rights reserved, Copyright Alleyne Technologies

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "ActiveGameplayEffectHandle.h"

#include "WaitCoolDownChange.generated.h"



struct FActiveGameplayEffectHandle;
struct FGameplayEffectSpec;
struct FGameplayTag;
class UAbilitySystemComponent;

//delegate list
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCoolDownChangeSignature, float, TimeRemaining);



/**
 * 
 */
UCLASS(BlueprintType, meta=(ExposedAsyncProxy = "ASyncTask"))
class HYPERLOOP_API UWaitCoolDownChange : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable) // creates the execution pins on the blueprint by making instances of the delegate
	FCoolDownChangeSignature CooldownStart;

	UPROPERTY(BlueprintAssignable)
	FCoolDownChangeSignature CooldownEnd;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true"))
	static UWaitCoolDownChange* WaitForCooldownChange(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayTag& InCooldownTag);

	UFUNCTION(BlueprintCallable)
	void EndTask();

protected:

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> ASC;
	
	FGameplayTag CooldownTag;
	
	void CooldownTagChanged(const FGameplayTag InCooldownTag, int32 NewCount);

	void OnActiveEffectAdded(UAbilitySystemComponent* TargetASC, const FGameplayEffectSpec& SpecApplied, FActiveGameplayEffectHandle ActiveAffectHandle);
	
};
