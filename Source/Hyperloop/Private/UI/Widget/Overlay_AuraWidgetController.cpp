// all rights reserved, Copyright Alleyne Technologies


#include "UI/Widget/Overlay_AuraWidgetController.h"
#include "GameplayEffectTypes.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

void UOverlay_AuraWidgetController::BroadcastInitialValues()
{
	//can remove for this example
	Super::BroadcastInitialValues();

	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);

	OnHealthChanged.Broadcast(AuraAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(AuraAttributeSet->GetMaxHealth());
	OnManaChanged.Broadcast(AuraAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(AuraAttributeSet->GetMaxMana());
	
}

void UOverlay_AuraWidgetController::BindCallbacksToDependencies() 
{
	
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetHealthAttribute()).AddUObject(this,&UOverlay_AuraWidgetController::HealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxHealthAttribute()).AddUObject(this,&UOverlay_AuraWidgetController::MaxHealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetManaAttribute()).AddUObject(this,&UOverlay_AuraWidgetController::ManaChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxManaAttribute()).AddUObject(this,&UOverlay_AuraWidgetController::MaxManaChanged);

	//the below can be used to replace the above call back functions which normally need to exsist for a delegate
	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda(
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
