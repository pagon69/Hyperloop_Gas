// all rights reserved, Copyright Alleyne Technologies

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"
#include "AuraProjectile.generated.h"

class UGameplayEffect;
struct FGameplayEffectSpecHandle;
class USphereComponent;
class UProjectileMovementComponent;
class UNiagaraSystem;


UCLASS()
class HYPERLOOP_API AAuraProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AAuraProjectile();

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true))
	FGameplayEffectSpecHandle DamageEffectSpecHandle;
	
	
protected:
	virtual void BeginPlay() override;

	virtual  void Destroyed() override;
	
	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
								int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


	
private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> Sphere;

	UPROPERTY(EditAnywhere) //for when it hits something
	TObjectPtr<UNiagaraSystem> ImpactEffect;

	UPROPERTY(EditAnywhere) // for the sound of impact
	TObjectPtr<USoundBase> ImpactSound;

	UPROPERTY(EditAnywhere) // for the sound of impact
	TObjectPtr<USoundBase> LoopingSound;

	bool bHit = false;

	UPROPERTY()
	TObjectPtr<UAudioComponent> LoopingSoundComponent; //returns after you spawn a sound and required to cancel the sound

	UPROPERTY(EditDefaultsOnly)
	float ProjectileLifeSpan = 15.0f;
};
