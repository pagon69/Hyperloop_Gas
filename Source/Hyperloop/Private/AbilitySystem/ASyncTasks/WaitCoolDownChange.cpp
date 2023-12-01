// all rights reserved, Copyright Alleyne Technologies


#include "AbilitySystem/ASyncTasks/WaitCoolDownChange.h"
#include  "AbilitySystemComponent.h"

UWaitCoolDownChange* UWaitCoolDownChange::WaitForCooldownChange(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayTag& InCooldownTag)
{

	UWaitCoolDownChange* WaitCooldownChange = NewObject<UWaitCoolDownChange>();
	WaitCooldownChange->ASC = AbilitySystemComponent;
	WaitCooldownChange->CooldownTag = InCooldownTag;
	
	if(!IsValid(AbilitySystemComponent) || !InCooldownTag.IsValid())
	{
		WaitCooldownChange->EndTask();
		return nullptr;
	}

	//calling the register event then adding the function - know when a cooldown effect has ended - cooldown tag removed
	AbilitySystemComponent->RegisterGameplayTagEvent(InCooldownTag, EGameplayTagEventType::NewOrRemoved).AddUObject(WaitCooldownChange,&UWaitCoolDownChange::CooldownTagChanged);


	//lets you know when an cooldown effect has added
	AbilitySystemComponent->OnActiveGameplayEffectAddedDelegateToSelf.AddUObject(WaitCooldownChange, &UWaitCoolDownChange::OnActiveEffectAdded);
	
	return WaitCooldownChange;
	
}

void UWaitCoolDownChange::EndTask()
{
	if(!IsValid(ASC)) return;
	
	ASC->RegisterGameplayTagEvent(CooldownTag, EGameplayTagEventType::NewOrRemoved).RemoveAll(this);

	SetReadyToDestroy();

	MarkAsGarbage();
}


void UWaitCoolDownChange::CooldownTagChanged(const FGameplayTag InCooldownTag, int32 NewCount)
{

	if(NewCount == 0)
	{
		CooldownEnd.Broadcast(0.f);
	}	

	

	
}

void UWaitCoolDownChange::OnActiveEffectAdded(UAbilitySystemComponent* TargetASC, const FGameplayEffectSpec& SpecApplied, FActiveGameplayEffectHandle ActiveAffectHandle)
{

	FGameplayTagContainer AssetTags;
	FGameplayTagContainer GrantedTags;
	
	SpecApplied.GetAllAssetTags(AssetTags);
	SpecApplied.GetAllGrantedTags(GrantedTags);

	if(AssetTags.HasTagExact(CooldownTag) || GrantedTags.HasTagExact(CooldownTag))
	{
		FGameplayEffectQuery GameplayEffectQuery = FGameplayEffectQuery::MakeQuery_MatchAnyOwningTags(CooldownTag.GetSingleTagContainer());

		TArray<float> TimesRemaining = ASC->GetActiveEffectsTimeRemaining(GameplayEffectQuery);

		if(TimesRemaining.Num() > 0)
		{
			
			float TimeRemaining = TimesRemaining[0];
			for( int32 i =0; i< TimesRemaining.Num() ;i++ )
			{
				if(TimesRemaining[i] > TimeRemaining)
				{
					TimeRemaining = TimesRemaining[i];
				}
				
			}
		CooldownStart.Broadcast(TimeRemaining);
		}
		
	}
	
	
}
