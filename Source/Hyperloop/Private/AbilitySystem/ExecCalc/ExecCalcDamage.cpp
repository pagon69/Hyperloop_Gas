// all rights reserved, Copyright Alleyne Technologies


#include "AbilitySystem/ExecCalc/ExecCalcDamage.h"
#include "AbilitySystemComponent.h"
#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "Interaction/CombatInterface.h"

struct AuraDamageStatics
{
	//the steps to create an attribute capture def - step 1
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	DECLARE_ATTRIBUTE_CAPTUREDEF(BlockChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArmorPenetration);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitDamage);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitResistance);
	
	AuraDamageStatics()
	{
		//the steps to create an attribute capture def  step 2
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Armor, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, BlockChance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, ArmorPenetration, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, CriticalHitChance, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, CriticalHitDamage, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, CriticalHitResistance, Target, false);
		
	}


	
	
};

static const AuraDamageStatics& DamageStatics()
{
	static AuraDamageStatics DStatics;

	return DStatics;
}



UExecCalcDamage::UExecCalcDamage()
{
	//the steps to create an attribute capture def - step 3
	RelevantAttributesToCapture.Add(DamageStatics().ArmorDef);
	RelevantAttributesToCapture.Add(DamageStatics().BlockChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().ArmorPenetrationDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitDamageDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitResistanceDef);

	
}



void UExecCalcDamage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	//default needed for everything to work
	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	AActor* SourceAvator = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	AActor* TargetAvator = TargetASC ? TargetASC->GetAvatarActor() : nullptr;

	ICombatInterface* SourceCombatInterface = Cast<ICombatInterface>(SourceAvator);
	ICombatInterface* TargetCombatInterface = Cast<ICombatInterface>(TargetAvator);
	
	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	const FGameplayTagContainer* SourceTag = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTag = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParameters;

	EvaluateParameters.SourceTags = SourceTag;
	EvaluateParameters.TargetTags = TargetTag;

	/*
	 * below are the secondary stats that i pull in to do calculations on
	 * 
	 */
	//get damage set by caller magnitude
	float Damage = Spec.GetSetByCallerMagnitude(FAuraGameplayTags::Get().Damage);

	// block chance capture - halve damage
	float TargetBlockChance = 0.f; // declare a variable
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().BlockChanceDef, EvaluateParameters, TargetBlockChance); // capture the block chance
	TargetBlockChance = FMath::Max<float>(0.f, TargetBlockChance);
	
	//armor 
	float TargetArmor = 0.f; // declare a variable
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorDef, EvaluateParameters, TargetArmor); // capture the block chance
	TargetArmor = FMath::Max<float>(0.f, TargetArmor);
	
	//armor penetration
	float SourceArmorPenetration = 0.f; // declare a variable
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorPenetrationDef, EvaluateParameters, SourceArmorPenetration); // capture the block chance
	SourceArmorPenetration = FMath::Max<float>(0.f, SourceArmorPenetration);

	//Critical Hit Chance
	float SourceCriticalHitChance = 0.f; // declare a variable
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitChanceDef, EvaluateParameters, SourceCriticalHitChance); // capture the block chance
	SourceCriticalHitChance = FMath::Max<float>(0.f, SourceCriticalHitChance);

	//Critical Hit Resistance
	float TargetCriticalHitResistance = 0.f; // declare a variable
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitResistanceDef, EvaluateParameters, TargetCriticalHitResistance); // capture the block chance
	TargetCriticalHitResistance = FMath::Max<float>(0.f, TargetCriticalHitResistance);

	//Critical Hit Damage
	float SourceCriticalHitDamage = 0.f; // declare a variable
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitDamageDef, EvaluateParameters, SourceCriticalHitDamage); // capture the block chance
	SourceCriticalHitDamage = FMath::Max<float>(0.f, SourceCriticalHitDamage);
	

	const UCharacterClassInfo* CharacterClassInfo = UAuraAbilitySystemLibrary::GetCharacterClassInfo(SourceAvator);

	//list of coeffeicents in curve table step 1 - must match curve names in IDe
	const FRealCurve* ArmorPenetrationCurve = CharacterClassInfo->DamageCalculationCoefficients->FindCurve(FName("ArmorPenetration"), FString());
	const FRealCurve* EffectiveArmorCurve = CharacterClassInfo->DamageCalculationCoefficients->FindCurve(FName("EffectiveArmor"), FString()); // check if the spelling is good
	const FRealCurve* CriticalHitResistanceCurve = CharacterClassInfo->DamageCalculationCoefficients->FindCurve(FName("CriticalHitResistance"), FString()); // check if the spelling is good

	//list of coeffeicents in curve table step 2
	const float ArmorPenetrationCoEff = ArmorPenetrationCurve->Eval(SourceCombatInterface->GetPlayerLevel()); // using the interface to pull level and provide to curve
	const float EffectiveArmorCoeff = EffectiveArmorCurve->Eval(TargetCombatInterface->GetPlayerLevel()); // using the interface to pull level and provide to curve
	const float CriticalHitResistanceCurveCoeff = CriticalHitResistanceCurve->Eval(TargetCombatInterface->GetPlayerLevel()); // using the interface to pull level and provide to curve
	

	/*
	 * Below are the varius calculations for damage using armor, and other secondary stats
	 */

	
	//checks if target block chance is higher than the results
	if(FMath::RandRange(1, 100) < TargetBlockChance)
	{
		Damage = Damage / 2.f;
	}


	
	//critical chance
	const float EffectiveCriticalHitChance = SourceCriticalHitChance - (TargetCriticalHitResistance * CriticalHitResistanceCurveCoeff); // another way to go

	if(FMath::RandRange(1, 100) < EffectiveCriticalHitChance)
	{
		Damage = ( Damage * 2.f ) + SourceCriticalHitDamage;
	}

	
	//armor pen formula and what it does
	const float EffectiveArmor = TargetArmor * ( 100 - SourceArmorPenetration * ArmorPenetrationCoEff ) / 100.f ;
	Damage *= ( 100 - EffectiveArmor * EffectiveArmorCoeff ) / 100.f;

	
	
	
	const FGameplayModifierEvaluatedData EvaluatedData(UAuraAttributeSet::GetIncomingDamageAttribute(),EGameplayModOp::Additive, Damage); // end result after secondary's
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}
