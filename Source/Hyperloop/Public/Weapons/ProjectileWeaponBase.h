// all rights reserved, Copyright Alleyne Technologies

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileWeaponBase.generated.h"

UCLASS(Abstract)
class HYPERLOOP_API AProjectileWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AProjectileWeaponBase();

protected:
	
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
