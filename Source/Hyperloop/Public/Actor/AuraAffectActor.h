// all rights reserved, Copyright Alleyne Technologies

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AuraAffectActor.generated.h"

class UGameplayEffect;

UCLASS()
class HYPERLOOP_API AAuraAffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AAuraAffectActor();

protected:
	
	virtual void BeginPlay() override;

	
	UPROPERTY(EditAnywhere, Category= "Applied Affects")
	TSubclassOf<UGameplayEffect> InstanceGameplayEffectClass;

	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* Target, TSubclassOf<UGameplayEffect> GameplayEffectClass);


	
};
