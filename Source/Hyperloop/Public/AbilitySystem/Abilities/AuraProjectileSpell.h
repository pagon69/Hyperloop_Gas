// all rights reserved, Copyright Alleyne Technologies

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/AuraGameplayAbility.h"
#include "AbilitySystem/Abilities/AuraDamageGameplayAbility.h"

#include "AuraProjectileSpell.generated.h"

struct FGameplayTag;
class AAuraProjectile;
/**
 * 
 */
UCLASS()
class HYPERLOOP_API UAuraProjectileSpell : public UAuraDamageGameplayAbility
{
	GENERATED_BODY()

public:

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UFUNCTION(BlueprintCallable, Category="Projectile")
	void SpawnProjectile(const FVector& ProjectileTargetLocation, const FGameplayTag& SocketTag, bool bOverridePitch = false, float PitchOverride = 0.f);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AAuraProjectile> ProjectileClass;


	//void PlaySoundInTransit();
	
private:

	//UPROPERTY(EditAnywhere)
	//TObjectPtr<USoundBase> TravelingSound;

};
