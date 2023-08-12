/* all rights reserved, Copyright Alleyne Technologies */


#include "UI/Widget/Overlay_EveWidgetController.h"

#include "AbilitySystem/EveAttributeSet.h"

void UOverlay_EveWidgetController::BroadcastInitialValues()
{
	//can remove for this example
	Super::BroadcastInitialValues();

	const UEveAttributeSet* EveAttributeSet = CastChecked<UEveAttributeSet>(AttributeSet);

	OnArmorChanged.Broadcast(EveAttributeSet->Armor.GetBaseValue());
	OnMaxArmorChanged.Broadcast(EveAttributeSet->MaxArmor.GetBaseValue());
	OnShieldChanged.Broadcast(EveAttributeSet->Shield.GetBaseValue());
	OnMaxShieldChanged.Broadcast(EveAttributeSet->MaxShield.GetBaseValue());
	OnCPUChanged.Broadcast(EveAttributeSet->CPU.GetBaseValue());
	OnMaxCPUChanged.Broadcast(EveAttributeSet->MaxCPU.GetBaseValue());
	
}
