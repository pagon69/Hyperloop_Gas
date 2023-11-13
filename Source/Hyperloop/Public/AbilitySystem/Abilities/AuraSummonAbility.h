// all rights reserved, Copyright Alleyne Technologies

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/AuraGameplayAbility.h"
#include "AuraSummonAbility.generated.h"

/**
 * 
 */
UCLASS()
class HYPERLOOP_API UAuraSummonAbility : public UAuraGameplayAbility
{
	GENERATED_BODY()

public:

	//the basic logic for the fucntion will be in bleuprints
	UFUNCTION(BlueprintCallable)
	TArray<FVector> GetSpawnLocations();

	UPROPERTY(EditDefaultsOnly, Category= "Summonning")
	int32 NumMinions = 5;

	UPROPERTY(EditDefaultsOnly, Category= "Summonning")
	TArray<TSubclassOf<APawn>> MinionClasses;

	UPROPERTY(EditDefaultsOnly, Category= "Summonning")
	float MinSpawnDistance = 50.f;

	UPROPERTY(EditDefaultsOnly, Category= "Summonning")
	float MaxSpawnDistance = 250.f;

	UPROPERTY(EditDefaultsOnly, Category= "Summonning")
	float SpawnSpreed = 90.f;
};
