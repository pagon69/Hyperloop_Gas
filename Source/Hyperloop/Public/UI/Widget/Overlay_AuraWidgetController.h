// all rights reserved, Copyright Alleyne Technologies

#pragma once

#include "CoreMinimal.h"
#include "UI/Widget/AuraWidgetController.h"
#include "Overlay_AuraWidgetController.generated.h"

class UAuraUserWidget;

USTRUCT(BlueprintType)
struct FUIWidgetRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag MessageTag = FGameplayTag(); //will hold the provided assettags from delegates
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Message = FText(); //something we can display in a widget to user

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UAuraUserWidget> MessageWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* Image = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float EffectMagnitute = 0;

	
};
//generic for any change made to attributes
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangedSignature, float, NewValue);

//how to make a dyanmic broadcast for vital assets - each below a specific declaraion for each attribute when it changes
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float, NewHealth);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSignature, float, NewMaxHealth);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaChangedSignature, float, NewMana);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxManaChangedSignature, float, NewMaxMana);

//for widget messages to be broadcast
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMessageWidgetRowSignature, FUIWidgetRow, Row);

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class HYPERLOOP_API UOverlay_AuraWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()

public:

	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Asttributes")
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Asttributes")
	FOnAttributeChangedSignature OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Asttributes")
	FOnAttributeChangedSignature OnManaChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Asttributes")
	FOnAttributeChangedSignature OnMaxManaChanged;


	// ghost globe area
	UPROPERTY(BlueprintAssignable, Category = "GAS|Asttributes")
	FOnAttributeChangedSignature OnGhostHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Asttributes")
	FOnAttributeChangedSignature OnMaxGhostHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Asttributes")
	FOnAttributeChangedSignature OnGhostManaChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Asttributes")
	FOnAttributeChangedSignature OnMaxGhostManaChanged;
	
	
	//for message widget - on change 
	UPROPERTY(BlueprintAssignable, Category = "GAS|Messages")
	FMessageWidgetRowSignature MessageWidgetRowDelegate;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Widget Data")
	TObjectPtr<UDataTable> MessageWidgetDataTable;

	//removed and replaced with lambda
	//void HealthChanged(const FOnAttributeChangeData& Data) const;
	
	//void MaxHealthChanged(const FOnAttributeChangeData& Data) const;
	//void ManaChanged(const FOnAttributeChangeData& Data) const;
	//void MaxManaChanged(const FOnAttributeChangeData& Data) const;

	template<typename T>
	T* GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag);


};

template <typename T>
T* UOverlay_AuraWidgetController::GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag)
{
	T* Row = DataTable->FindRow<T>(Tag.GetTagName(), TEXT(""));

	return Row;

	//smarter way would be: return DataTable->FindRow<T>(Tag.GetTagName(), TEXT(""));
	
}
