// all rights reserved, Copyright Alleyne Technologies


#include "UI/Widget/EveWidgetController.h"

void UEveWidgetController::SetWidgetControllerParameters(const FWidgetControllerParameters& WcParams)
{
	PlayerController = WcParams.PlayerController;
	PlayerState = WcParams.PlayerState;
	AbilitySystemComponent = WcParams.AbilitySystemComponent;
	AttributeSet = WcParams.AttributeSet;
	
}

void UEveWidgetController::BroadcastInitialValues()
{
	//update in deriaved classes
}
