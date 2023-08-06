// all rights reserved, Copyright Alleyne Technologies


#include "GamePlayUtility/EvePlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "Interaction/MouseTargetInterface.h"

AEvePlayerController::AEvePlayerController()
{
	bReplicates = true;
}

void AEvePlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(EveContext); // check if movement is setup or not - crash if not

	//required for the enhanced input to work - just a boil-aplate thing
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	check(Subsystem); //checks to make sure it is valid then sets
	Subsystem->AddMappingContext(EveContext, 0);

	// setup stuff for mouse - check here for different mouse cursors
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
	
	
}

void AEvePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	Super::SetupInputComponent();
    	
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AEvePlayerController::Move);

}

void AEvePlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}


void AEvePlayerController::CursorTrace()
{

	//make a line trace under the cursor, a member function of player controller class
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if(!CursorHit.bBlockingHit) return;
	
	LastActor = ThisActor;
	ThisActor = Cast<IMouseTargetInterface>(CursorHit.GetActor());

	// Logic for below documented in Auraplayer controller

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



void AEvePlayerController::Move(const FInputActionValue& InputActionValue)
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

