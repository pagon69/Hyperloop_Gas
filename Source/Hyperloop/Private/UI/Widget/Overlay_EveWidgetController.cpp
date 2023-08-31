/* all rights reserved, Copyright Alleyne Technologies */


#include "UI/Widget/Overlay_EveWidgetController.h"
#include "GameplayEffectTypes.h"
#include "AbilitySystem/EveAttributeSet.h"

void UOverlay_EveWidgetController::BroadcastInitialValues()
{
	//can remove for this example
	//Super::BroadcastInitialValues();

	const UEveAttributeSet* EveAttributeSet = CastChecked<UEveAttributeSet>(AttributeSet);

	OnArmorChanged.Broadcast(EveAttributeSet->GetArmor());
	OnMaxArmorChanged.Broadcast(EveAttributeSet->GetMaxArmor());
	OnShieldChanged.Broadcast(EveAttributeSet->GetShield());
	OnMaxShieldChanged.Broadcast(EveAttributeSet->GetMaxShield());
	OnCPUChanged.Broadcast(EveAttributeSet->GetCPU());
	OnMaxCPUChanged.Broadcast(EveAttributeSet->GetMaxCPU());
	
}

void UOverlay_EveWidgetController::BindCallbacksToDependencies()
{

	const UEveAttributeSet* EveAttributeSet = CastChecked<UEveAttributeSet>(AttributeSet);
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(EveAttributeSet->GetArmorAttribute()).AddUObject(this,&UOverlay_EveWidgetController::ArmorChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(EveAttributeSet->GetMaxArmorAttribute()).AddUObject(this,&UOverlay_EveWidgetController::MaxArmorChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(EveAttributeSet->GetShieldAttribute()).AddUObject(this,&UOverlay_EveWidgetController::ShieldChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(EveAttributeSet->GetMaxShieldAttribute()).AddUObject(this,&UOverlay_EveWidgetController::MaxShieldChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(EveAttributeSet->GetCPUAttribute()).AddUObject(this,&UOverlay_EveWidgetController::CPUChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(EveAttributeSet->GetMaxCPUAttribute()).AddUObject(this,&UOverlay_EveWidgetController::MaxCPUChanged);

	
}

void UOverlay_EveWidgetController::ArmorChanged(const FOnAttributeChangeData& Data) const
{

	OnArmorChanged.Broadcast(Data.NewValue);
	
}

void UOverlay_EveWidgetController::MaxArmorChanged(const FOnAttributeChangeData& Data) const
{
	
	OnMaxArmorChanged.Broadcast(Data.NewValue);

}

void UOverlay_EveWidgetController::ShieldChanged(const FOnAttributeChangeData& Data) const
{

	OnShieldChanged.Broadcast(Data.NewValue);

}

void UOverlay_EveWidgetController::MaxShieldChanged(const FOnAttributeChangeData& Data) const
{

	OnMaxShieldChanged.Broadcast(Data.NewValue);

}

void UOverlay_EveWidgetController::CPUChanged(const FOnAttributeChangeData& Data) const
{
	
	OnCPUChanged.Broadcast(Data.NewValue);
	
}

void UOverlay_EveWidgetController::MaxCPUChanged(const FOnAttributeChangeData& Data) const
{

	OnMaxCPUChanged.Broadcast(Data.NewValue);
	
}
