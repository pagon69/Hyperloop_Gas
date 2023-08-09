// all rights reserved, Copyright Alleyne Technologies


#include "UI/Widget/EveUserWidget.h"

void UEveUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
