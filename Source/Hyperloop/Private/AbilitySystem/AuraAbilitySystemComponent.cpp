// all rights reserved, Copyright Alleyne Technologies


#include "AbilitySystem/AuraAbilitySystemComponent.h"

//finds when an effect is applied
void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::EffectApplied);
}

void UAuraAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent,
                                                const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{

	FGameplayTagContainer TagContainer;

	EffectSpec.GetAllAssetTags(TagContainer);

	//when an affect is applied the ability system component will broadcast this TagContainer component to anyone listening
	EffectAssetTags.Broadcast(TagContainer); // use to broadcast the delegate
	
}
