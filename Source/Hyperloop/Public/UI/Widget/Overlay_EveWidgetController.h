// all rights reserved, Copyright Alleyne Technologies

#pragma once

#include "CoreMinimal.h"
#include "UI/Widget/EveWidgetController.h"
#include "GameplayEffectTypes.h"
#include "Overlay_EveWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnArmorChangedSignature, float, NewArmor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxArmorChangedSignature, float, NewMaxArmor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnShieldChangedSignature, float, NewShield);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxShieldChangedSignature, float, NewMaxShield);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCPUChangedSignature, float, NewCPU);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxCPUChangedSignature, float, NewMaxCPU);

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class HYPERLOOP_API UOverlay_EveWidgetController : public UEveWidgetController
{
	GENERATED_BODY()

public:

	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Asttributes")
	FOnArmorChangedSignature OnArmorChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Asttributes")
	FOnMaxArmorChangedSignature OnMaxArmorChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Asttributes")
	FOnShieldChangedSignature OnShieldChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Asttributes")
	FOnMaxShieldChangedSignature OnMaxShieldChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Asttributes")
	FOnCPUChangedSignature OnCPUChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Asttributes")
	FOnMaxCPUChangedSignature OnMaxCPUChanged;
	
protected:
	
	void ArmorChanged(const FOnAttributeChangeData& Data) const;
	void MaxArmorChanged(const FOnAttributeChangeData& Data) const;
	void ShieldChanged(const FOnAttributeChangeData& Data) const;
	void MaxShieldChanged(const FOnAttributeChangeData& Data) const;
	void CPUChanged(const FOnAttributeChangeData& Data) const;
	void MaxCPUChanged(const FOnAttributeChangeData& Data) const;
	
};
