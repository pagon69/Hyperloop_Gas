// all rights reserved, Copyright Alleyne Technologies


#include "UI/HUD/EveHUD.h"
#include "UI/Widget/EveUserWidget.h"
#include "Blueprint/UserWidget.h"
#include "UI/Widget/Overlay_EveWidgetController.h"


UOverlay_EveWidgetController* AEveHUD::GetOverlayWidgetController(const FWidgetControllerParameters& WcParams)
{
	//if null make one else return the one we have
	if(OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlay_EveWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParameters(WcParams);

		OverlayWidgetController->BindCallbacksToDependencies();
		
		return  OverlayWidgetController;
	}
	
	return OverlayWidgetController;
	
}

void AEveHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass, TEXT("Overlay widget class uninitialized, please fillout BP_auraHUD"));
	checkf(OverlayWidgetControllerClass, TEXT("Overlay widget controller class uninitialized, please fillout BP_auraHUD"))

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UEveUserWidget>(Widget);
	
	const FWidgetControllerParameters WidgetControllerParameters(PC, PS, ASC, AS);
	UOverlay_EveWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParameters);

	OverlayWidget->SetWidgetController(WidgetController);

	WidgetController->BroadcastInitialValues(); //does broadcast here
	
	Widget->AddToViewport();
	
}


/*
void AEveHUD::BeginPlay()
{
	Super::BeginPlay();

	//UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	
	Widget->AddToViewport();
}
*/
