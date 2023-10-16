// all rights reserved, Copyright Alleyne Technologies


#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraGameplayAbility.h"


//finds when an effect is applied
void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::ClientEffectApplied);

	const FAuraGameplayTags& GameplayTags = FAuraGameplayTags::Get();

	//GameplayTags.
	
}

void UAuraAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartUpAbilities)
{
	for(const TSubclassOf<UGameplayAbility> AbilityClass : StartUpAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		
		if(const UAuraGameplayAbility* AuraAbility = Cast<UAuraGameplayAbility>(AbilitySpec.Ability))
		{
			AbilitySpec.DynamicAbilityTags.AddTag(AuraAbility->StartupInputTag);
			GiveAbility(AbilitySpec);
		}
		
		//GiveAbilityAndActivateOnce(AbilitySpec); //gives an ability then starts it
		
	}
	
}

void UAuraAbilitySystemComponent::AbilityInputTagHeld(const FGameplayTag& InputTag)
{
	if(!InputTag.IsValid()) return;

	for(auto& AbilitySpec : GetActivatableAbilities()) // can replace auto with the class definition if needed
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpecInputPressed(AbilitySpec); //flag to track the input being pressed
			
			if(!AbilitySpec.IsActive())
			{
				TryActivateAbility(AbilitySpec.Handle); // way to use an ability
			}
		}
	}
	
}

void UAuraAbilitySystemComponent::AbilityInputTagRelease(const FGameplayTag& InputTag)
{
	if(!InputTag.IsValid()) return;

	for(auto& AbilitySpec : GetActivatableAbilities()) // can replace auto with the class definition if needed
		{
			if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
			{
				AbilitySpecInputReleased(AbilitySpec); //flag to track the input being pressed
			
			}
		}
}

void UAuraAbilitySystemComponent::ClientEffectApplied_Implementation(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{

	FGameplayTagContainer TagContainer;

	EffectSpec.GetAllAssetTags(TagContainer);

	//when an affect is applied the ability system component will broadcast this TagContainer component to anyone listening
	EffectAssetTags.Broadcast(TagContainer); // use to broadcast the delegate
	
}
