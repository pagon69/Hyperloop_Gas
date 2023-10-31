#pragma once

#include "GameplayEffectTypes.h"
#include "AuraAbilityTypes.generated.h"


USTRUCT(BlueprintType)
struct FAuraGameplayEffectContext : public FGameplayEffectContext
{
	GENERATED_BODY()

public:

	virtual UScriptStruct* GetScriptStruct() const override;
	
	//for how to send data over a network
	virtual  bool NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess) override;

	// inline getters
	bool IsCriticalHit() const { return bIsCriticalHit; }
	bool IsBlockedHit() const { return bIsBlockedHit; }

	//inline setter
	void SetIsCriticalHit (bool bInIsCriticalHit) { bIsCriticalHit = bInIsCriticalHit; }
	void SetIsBlockedHit (bool bInIsBlockedHit) {bIsBlockedHit = bInIsBlockedHit; }
	
	
protected:


	UPROPERTY()
	bool bIsBlockedHit = false;
	
	UPROPERTY()
	bool bIsCriticalHit = false;
	

	
};
