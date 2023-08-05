// all rights reserved, Copyright Alleyne Technologies

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "EveCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

/**
 * 
 */
UCLASS()
class HYPERLOOP_API AEveCharacter : public ACharacterBase
{
	GENERATED_BODY()

public:
	AEveCharacter();
	
protected:

	UPROPERTY(EditAnywhere, Category= "Camera View")
	TObjectPtr<USpringArmComponent> CameraBoon;
	
	UPROPERTY(EditAnywhere, Category= "Camera View")
	TObjectPtr<UCameraComponent> Camera;
	
private:
	

	
};
