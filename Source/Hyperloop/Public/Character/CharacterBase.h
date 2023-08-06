// all rights reserved, Copyright Alleyne Technologies

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

#define CUSTOM_DEPTH_RED 250


UCLASS(Abstract)
class HYPERLOOP_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	
	ACharacterBase();

protected:
	
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category= "Combat")
	TObjectPtr<USkeletalMeshComponent> SkeletalWeapon;

	UPROPERTY(EditAnywhere, Category= "Combat")
	TObjectPtr<UStaticMeshComponent> StaticWeapon;

	
	
};
