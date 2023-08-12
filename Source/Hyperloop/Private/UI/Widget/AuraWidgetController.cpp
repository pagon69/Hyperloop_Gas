// all rights reserved, Copyright Alleyne Technologies


#include "UI/Widget/AuraWidgetController.h"
#include "AbilitySystemComponent.h"

void UAuraWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WcParams)
{
	PlayerController = WcParams.PlayerController;
	PlayerState = WcParams.PlayerState;
	AbilitySystemComponent = WcParams.AbilitySystemComponent;
	AttributeSet = WcParams.AttributeSet;
	
}

void UAuraWidgetController::BroadcastInitialValues()
{
	//override in direaved classes
}
