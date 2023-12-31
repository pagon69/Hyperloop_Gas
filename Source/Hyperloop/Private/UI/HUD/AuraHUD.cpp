// all rights reserved, Copyright Alleyne Technologies


#include "UI/HUD/AuraHUD.h"
#include "Blueprint/UserWidget.h"
#include "UI/Widget/AuraUserWidget.h"
#include "UI/Widget/Overlay_AuraWidgetController.h"
#include "UI/Widget/AttributeMenuWidgetController.h"


//for the overlay widget
UOverlay_AuraWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WcParams)
{

	if(OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlay_AuraWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WcParams);
		
		OverlayWidgetController->BindCallbacksToDependencies();

	//	return  OverlayWidgetController;
	}
	return OverlayWidgetController;
}

//for the attribute menu
UAttributeMenuWidgetController* AAuraHUD::GetAttributeMenuWidgetController(const FWidgetControllerParams& WcParams)
{
	if(AttributeMenuWidgetController == nullptr)
	{
		AttributeMenuWidgetController = NewObject<UAttributeMenuWidgetController>(this, AttributeMenuWidgetControllerClass);
		AttributeMenuWidgetController->SetWidgetControllerParams(WcParams);
		
		AttributeMenuWidgetController->BindCallbacksToDependencies();
	}
	return AttributeMenuWidgetController;
	
}

void AAuraHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass, TEXT("Overlay widget class uninitialized, please fillout BP_auraHUD"));
	checkf(OverlayWidgetControllerClass, TEXT("Overlay widget controller class uninitialized, please fillout BP_auraHUD"))
	
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UAuraUserWidget>(Widget);
	
	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	UOverlay_AuraWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);
	
	OverlayWidget->SetWidgetController(WidgetController);

	WidgetController->BroadcastInitialValues(); //does broadcast here
	
	Widget->AddToViewport();
	
}

/*
void AAuraHUD::BeginPlay()
{
	Super::BeginPlay();

	//adds the widget to the view port
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	Widget->AddToViewport();

	
}
*/