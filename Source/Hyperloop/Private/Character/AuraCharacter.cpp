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
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	//init ability actor info for client
	InitAbilityActorInfo();
}

void AAuraCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAuraCharacter::InitAbilityActorInfo() 
{
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>(); //get the current player state

	//check(AuraPlayerState);  // make sure no null pointer

	if(AuraPlayerState)
	{
		AuraPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(AuraPlayerState, this);

		Cast<UAuraAbilitySystemComponent>(AuraPlayerState->GetAbilitySystemComponent())->AbilityActorInfoSet();
		
		AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
		AttributeSet = AuraPlayerState->GetAttributeSet();

		InitializePrimaryAttributes();
		
		if (AAuraPlayerController* AuraPlayerController = Cast<AAuraPlayerController>(GetController()))
		{
			if (AAuraHUD* AuraHUD = Cast<AAuraHUD>(AuraPlayerController->GetHUD()))
			{
				AuraHUD->InitOverlay(AuraPlayerController,AuraPlayerState,AbilitySystemComponent,AttributeSet);
			}
		}
		
	}

	
}
