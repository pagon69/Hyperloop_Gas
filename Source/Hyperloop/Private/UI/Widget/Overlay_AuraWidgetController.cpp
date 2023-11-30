// all rights reserved, Copyright Alleyne Technologies


#include "UI/Widget/Overlay_AuraWidgetController.h"
#include "GameplayEffectTypes.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AbilityInfo.h"

void UOverlay_AuraWidgetController::BroadcastInitialValues()
{
	//can remove for this example
	Super::BroadcastInitialValues();

	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);

	//normal health bar
	OnHealthChanged.Broadcast(AuraAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(AuraAttributeSet->GetMaxHealth());
	OnManaChanged.Broadcast(AuraAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(AuraAttributeSet->GetMaxMana());
	/*

	//trailing ghost bar
	OnGhostHealthChanged.Broadcast(AuraAttributeSet->GetGhostHealth());
	OnMaxGhostHealthChanged.Broadcast(AuraAttributeSet->GetMaxGhostHealth());	
	OnGhostManaChanged.Broadcast(AuraAttributeSet->GetGhostMana());
	OnMaxGhostManaChanged.Broadcast(AuraAttributeSet->GetMaxGhostMana());
    */

	
	//Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)
	//[](){};
	
	
}

void UOverlay_AuraWidgetController::BindCallbacksToDependencies() 
{
	
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);

	//one way to do this while lambda is another way
//	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetHealthAttribute()).AddUObject(this,&UOverlay_AuraWidgetController::HealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetHealthAttribute()).AddLambda(
	[this](const FOnAttributeChangeData& Data)
		{
			OnHealthChanged.Broadcast(Data.NewValue);
		}
	);

	//converted to a lambda
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxHealthAttribute()).AddLambda(
	[this](const FOnAttributeChangeData& Data)
		{
			OnMaxHealthChanged.Broadcast(Data.NewValue);
		}
	);

	//mana lambda
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnManaChanged.Broadcast(Data.NewValue);
		}

	);

	//maxmana lambda
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxManaAttribute()).AddLambda(
	[this](const FOnAttributeChangeData& Data)
		{
			OnMaxManaChanged.Broadcast(Data.NewValue);
		}

	);


	

	
/*
	
	//trailing ghost lambdas for changes
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetGhostHealthAttribute()).AddLambda(
	[this](const FOnAttributeChangeData& Data)
		{
			OnGhostHealthChanged.Broadcast(Data.NewValue);
		}

	);

 */

	/*
	 *
	//trailing max ghost health lambda
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxGhostHealthAttribute()).AddLambda(
	[this](const FOnAttributeChangeData& Data)
		{
			OnMaxGhostHealthChanged.Broadcast(Data.NewValue);
		}

	);

*/
	/*
	//trailing ghost mana lambdas for changes
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetGhostManaAttribute()).AddLambda(
	[this](const FOnAttributeChangeData& Data)
		{
			OnGhostManaChanged.Broadcast(Data.NewValue);
		}

	);

	*/
	
/*	
	
	//trailing max ghost mana lambda
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxGhostManaAttribute()).AddLambda(
	[this](const FOnAttributeChangeData& Data)
		{
			OnMaxGhostManaChanged.Broadcast(Data.NewValue);
		}

	);
	
*/
	


	if(UAuraAbilitySystemComponent* AuraASC = Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent))
	{
		
		if(AuraASC->bStartupAbilitiesGiven)
		{
			OnInitializeStartupAbilities(AuraASC);
		}

		else
		{
			AuraASC->AbilitiesGivenDelegate.AddUObject(this, &UOverlay_AuraWidgetController::OnInitializeStartupAbilities);
		}
		
	//the below can be used to replace the above call back functions which normally need to exsist for a delegate
		AuraASC->EffectAssetTags.AddLambda(
		[this](const FGameplayTagContainer& AssetTags)  //makes a lambda - a lambda seems like a inline function  //the this keyword is needed to call member functions in a lambda
			{
			//gets asset tags from effect or object interaction
					for (const FGameplayTag& Tag : AssetTags)
					{
						FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message")); //looks for a Tag with the name Message in it and returns it
					
					
					//const FString Msg = FString::Printf(TEXT("GE Tag: %s"), *Tag.ToString());
					//GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Blue, Msg, true);

						if(Tag.MatchesTag(MessageTag))
						{
							const FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
							MessageWidgetRowDelegate.Broadcast(*Row);
						}
					
					}

			
			}
		
		);
	
	}
	
}

//find abilities on the ability system component
//WHEN THIS IS CALLED WE CREATE A LAMDA AND BInd to it
// the lambda then gets the tags info and  broadcast it
void UOverlay_AuraWidgetController::OnInitializeStartupAbilities(UAuraAbilitySystemComponent* AuraAbilitySystemComponent)
{
	//todo: get info about all given abilities, then look up and broadcast

	if(!AuraAbilitySystemComponent->bStartupAbilitiesGiven) return;

	//the search happens here
	FForEachAbility BroadCastDelegate;
	BroadCastDelegate.BindLambda([this, AuraAbilitySystemComponent](const FGameplayAbilitySpec& AbilitySpec)
	{
		
		FAuraAbilityInfo Info =	AbilityInfo->FindAbilityInfoForTag(AuraAbilitySystemComponent->GetAbilityTagFromSpec(AbilitySpec));
		Info.InputTag = AuraAbilitySystemComponent->GetInputTagFromSpec(AbilitySpec);
		AbilityInfoDelegate.Broadcast(Info);
		
	});

	AuraAbilitySystemComponent->ForEachAbility(BroadCastDelegate);
	
}



/*  sample of callback functions without lambda
void UOverlay_AuraWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlay_AuraWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{

	OnMaxHealthChanged.Broadcast(Data.NewValue);
	
}

void UOverlay_AuraWidgetController::ManaChanged(const FOnAttributeChangeData& Data) const
{
	
	OnManaChanged.Broadcast(Data.NewValue);
	
}

void UOverlay_AuraWidgetController::MaxManaChanged(const FOnAttributeChangeData& Data) const
{
	
	OnMaxManaChanged.Broadcast(Data.NewValue);
}

*/
