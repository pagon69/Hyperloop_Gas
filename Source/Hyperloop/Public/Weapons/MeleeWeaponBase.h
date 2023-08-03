// all rights reserved, Copyright Alleyne Technologies

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MeleeWeaponBase.generated.h"

UCLASS(Abstract)
class HYPERLOOP_API AMeleeWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AMeleeWeaponBase();

protected:
	
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
