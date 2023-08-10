// all rights reserved, Copyright Alleyne Technologies


#include "UI/HUD/EveHUD.h"
#include "UI/Widget/EveUserWidget.h"
#include "Blueprint/UserWidget.h"


void AEveHUD::BeginPlay()
{
	Super::BeginPlay();

	//UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	
	Widget->AddToViewport();
}
