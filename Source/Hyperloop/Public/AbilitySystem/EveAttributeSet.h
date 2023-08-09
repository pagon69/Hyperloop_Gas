// all rights reserved, Copyright Alleyne Technologies

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "EveAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class HYPERLOOP_API UEveAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UEveAttributeSet();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	

	//the following 4 lines required per attribute
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Armor, Category = "Vital Attributes")
	FGameplayAttributeData Armor;

	UFUNCTION()
	void OnRep_Armor(const FGameplayAttributeData& OldArmor) const;
	/**********************     Armor      ***************************/

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxArmor, Category = "Vital Attributes")
	FGameplayAttributeData MaxArmor;

	UFUNCTION()
	void OnRep_MaxArmor(const FGameplayAttributeData& OldMaxArmor) const;
	/**********************    Max Armor         ***************************/

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Shield, Category = "Vital Attributes")
	FGameplayAttributeData Shield;

	UFUNCTION()
	void OnRep_Shield(const FGameplayAttributeData& OldShield) const;

	/**********************    Shield      ***************************/

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxShield, Category = "Vital Attributes")
	FGameplayAttributeData MaxShield;

	UFUNCTION()
	void OnRep_MaxShield(const FGameplayAttributeData& OldMaxShield) const;

	/**********************     Max Shield         ***************************/

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CPU, Category = "Vital Attributes")
	FGameplayAttributeData CPU;

	UFUNCTION()
	void OnRep_CPU(const FGameplayAttributeData& OldCPU) const;

	/**********************    CPU        ***************************/
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxCPU, Category = "Vital Attributes")
	FGameplayAttributeData MaxCPU;

	UFUNCTION()
	void OnRep_MaxCPU(const FGameplayAttributeData& OldMaxCPU) const;

	/**********************    CPU        ***************************/
protected:
	
	
};
