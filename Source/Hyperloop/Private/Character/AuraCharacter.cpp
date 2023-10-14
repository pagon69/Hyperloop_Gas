// all rights reserved, Copyright Alleyne Technologies


#include "Character/AuraCharacter.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Character/AuraPlayerState.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GamePlayUtility/AuraPlayerController.h"
#include "UI/HUD/AuraHUD.h"

AAuraCharacter::AAuraCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	//AbilitySystemComponent->getabilitysystemcomponent
	
}

void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	//init ability actor info for server 
	InitAbilityActorInfo();  /* this fails on server everytime but works on client */

	//grants abilities -- causes a crash here
	//AddCharacterAbilities();
	
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	//init ability actor info for client
	InitAbilityActorInfo();

	//grants abilities
	//AddCharacterAbilities();
	
}


void AAuraCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAuraCharacter::InitAbilityActorInfo() 
{
	//gets the player state
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>(); //get the current player state

	//check(AuraPlayerState);  // make sure no null pointer

	if(AuraPlayerState)
	{
		AuraPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(AuraPlayerState, this);

		Cast<UAuraAbilitySystemComponent>(AuraPlayerState->GetAbilitySystemComponent())->AbilityActorInfoSet();
		
		AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
		AttributeSet = AuraPlayerState->GetAttributeSet();

		InitializeDefaultAttributes();

		//grants abilities
		AddCharacterAbilities(); // can i put this some place esle ?
	
		if (AAuraPlayerController* AuraPlayerController = Cast<AAuraPlayerController>(GetController()))
		{
			if (AAuraHUD* AuraHUD = Cast<AAuraHUD>(AuraPlayerController->GetHUD()))
			{
				AuraHUD->InitOverlay(AuraPlayerController,AuraPlayerState,AbilitySystemComponent,AttributeSet);
			}
		}

		
	}

	
}

int32 AAuraCharacter::GetPlayerLevel()
{
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>(); //get the current player state

	// causes a crash some times
	check(AuraPlayerState);
	
	return AuraPlayerState->GetPlayerLevel();
}
