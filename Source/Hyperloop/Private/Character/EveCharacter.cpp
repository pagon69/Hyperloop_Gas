// all rights reserved, Copyright Alleyne Technologies


#include "Character/EveCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


AEveCharacter::AEveCharacter()
{
	CameraBoon = CreateDefaultSubobject<USpringArmComponent>("CameraBoon");
	CameraBoon->SetupAttachment(GetRootComponent());

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(CameraBoon);

	//tweaked the settings for the various controls
	CameraBoon->bEnableCameraLag = true;
	CameraBoon->bInheritPitch = false;
	CameraBoon->bInheritRoll = false;
	CameraBoon->bInheritYaw = false;
	
	Camera->bUsePawnControlRotation = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	
	
}
