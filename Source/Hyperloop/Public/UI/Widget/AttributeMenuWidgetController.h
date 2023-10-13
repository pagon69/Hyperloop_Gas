// all rights reserved, Copyright Alleyne Technologies

#pragma once

#include "CoreMinimal.h"
#include "UI/Widget/AuraWidgetController.h"
#include "AttributeMenuWidgetController.generated.h"


class UAttributeInfo;

struct FAuraAttributeInfo;

//how to do delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam (FAuraAttributeInfoSignature, const FAuraAttributeInfo&, Info);




/**
 * 
 */
UCLASS(BlueprintType, Blueprintable) // required to make a blueprint of teh class later
class HYPERLOOP_API UAttributeMenuWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()

public:
	virtual void BindCallbacksToDependencies() override;

	virtual void BroadcastInitialValues() override;

	UPROPERTY(BlueprintAssignable, Category ="GAS|Attributes") //next part of doing delegates
	FAuraAttributeInfoSignature AttributeInfoDelegate;

	
protected:

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAttributeInfo> AttributeInfo;

private:

	void BroadCastAttributeInfo(const FGameplayTag& AttributeTag, const FGameplayAttribute& Attribute) const;
};
