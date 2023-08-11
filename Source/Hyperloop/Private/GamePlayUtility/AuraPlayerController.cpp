// all rights reserved, Copyright Alleyne Technologies


#include "GamePlayUtility/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "Interaction/MouseTargetInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	check(AuraContext); // check if movement is setup or not - crash if not

	//required for the enhanced input to work - just a boil-aplate thing
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	if(Subsystem) //checks to make sure it is valid then sets
	{
		Subsystem->AddMappingContext(AuraContext, 0);
	}
	
	// setup stuff for mouse - check here for different mouse coursors
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
	
}

//required to do input within player controller
void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered,this, &AAuraPlayerController::Move);

}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}

void AAuraPlayerController::CursorTrace()
{
	//make a line trace under the cursor, a member function of player controller class
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if(!CursorHit.bBlockingHit) return;
	
	LastActor = ThisActor;
	ThisActor = Cast<IMouseTargetInterface>(CursorHit.GetActor());

	/**
	 *Line trace from actor, there are several scenarios:
	 *  A. Last actor is null && this actor is null
	 *	- D nothing
	 *	B. Last actor is null && this actor is valid
	 *	- Highlight this actor
	 *	C. Last actor is valid && this actor is Null
	 *	-	Unhighlight LastActor
	 *	D. Both Actors are valid, but Last actor != this actor
	 * - Unhighlight Lastactor and Highlight This actor
	 * E. Both actors are valid and are the same actor
	 * - Do Nothing
	*/

	if(LastActor == nullptr)
	{
		if(ThisActor != nullptr)
		{
			//case B
			ThisActor->HighLightActor();
		}
		else
		{
			//case A - both or null do nothing
		}
	}
	else
	{
		if(ThisActor == nullptr)
		{
			//Case C
			LastActor->UnHighLightActor();
		}
		else  // both actors valid
		{
			if(LastActor != ThisActor)
			{
				LastActor->UnHighLightActor();
				ThisActor->HighLightActor();
			}
			else
			{
				//case E- Do nothing
			}
		}
	}
	
}


void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{

	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}



}

