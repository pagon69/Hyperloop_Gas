// all rights reserved, Copyright Alleyne Technologies


#include "UI/Widget/Overlay_AuraWidgetController.h"
#include "GameplayEffectTypes.h"
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
