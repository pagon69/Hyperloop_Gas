// all rights reserved, Copyright Alleyne Technologies


#include "UI/Widget/AttributeMenuWidgetController.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"
#include "AuraGameplayTags.h"

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	Super::BindCallbacksToDependencies();

	
}

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	Super::BroadcastInitialValues();

	UAuraAttributeSet* AS = CastChecked<UAuraAttributeSet>(AttributeSet);

	check(AttributeInfo)

	FAuraAttributeInfo Info = AttributeInfo->FindAttributeInfoFromTag(FAuraGameplayTags::Get().Attributes_Primary_Strength);
	Info.AttributeValue = AS->GetStrenght();
	AttributeInfoDelegate.Broadcast(Info);
	
}
