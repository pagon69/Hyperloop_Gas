// all rights reserved, Copyright Alleyne Technologies


#include "GamePlayUtility/AuraPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AuraGameplayTags.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Components/SplineComponent.h"
#include "Input/AuraInputComponent.h"
#include "Interaction/MouseTargetInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;

	//creates the spline in game with no points or anything to it
	Spline = CreateDefaultSubobject<USplineComponent>("Spline");
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
	
	//UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	//binds action is how to do the input component in blueprint
//	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered,this, &AAuraPlayerController::Move);

//custom input componetnt
	UAuraInputComponent* AuraInputComponent = CastChecked<UAuraInputComponent>(InputComponent);

	//binds action is how to do the input component in blueprint
	AuraInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered,this, &AAuraPlayerController::Move);
	AuraInputComponent->BindAction(SwiftAction, ETriggerEvent::Started,this, &AAuraPlayerController::SwiftPress);
	AuraInputComponent->BindAction(SwiftAction, ETriggerEvent::Completed,this, &AAuraPlayerController::SwiftRelease);
	AuraInputComponent->BindAction(OpenMenuAction, ETriggerEvent::Triggered,this, &AAuraPlayerController::OpenMenu);
	AuraInputComponent->BindAction(SwiftAction, ETriggerEvent::Triggered,this, &AAuraPlayerController::Swift);

	AuraInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::AbilityInputTagPress, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();

	AutoRun();
	
}

void AAuraPlayerController::CursorTrace()
{
	//make a line trace under the cursor, a member function of player controller class
	
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if(!CursorHit.bBlockingHit) return;
	
	LastActor = ThisActor;
	ThisActor = Cast<IMouseTargetInterface>(CursorHit.GetActor()); // keeps a value of an enemy if they are being highlighted

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

void AAuraPlayerController::AbilityInputTagPress(FGameplayTag InputTag) 
{
	
	
	// bIsTargeting = ThisActor ? true :false; // if thisactor is null returns false but returns true if it is something

	//if ThisActor contains a target to highlight then bIsTargeting is true
	//bAutoRunning = false; // uncomment the above two lines and remove my if not working

	if(InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB))
	{
		bIsTargeting = ThisActor ? true : false;
		bAutoRunning = false;
	}
	
}

void AAuraPlayerController::AbilityInputTagReleased(FGameplayTag InputTag) 
{

	if(!InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB)) //checks if a LMB ability was used
		{
			if(GetAsc())
			{
				GetAsc()->AbilityInputTagRelease(InputTag);
			}
			return;
		}

	if(GetAsc()) GetAsc()->AbilityInputTagRelease(InputTag);
	
	if( !bIsTargeting && !bSwiftKeyPressed) // checks if you are hovering over a enemy
		{
			APawn* ControlledPawn = GetPawn();
			if(FollowTime <= ShortPressThreshold && ControlledPawn)
			{
				UNavigationPath* NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(this, ControlledPawn->GetActorLocation(), CacheDestination );
				if(NavPath)
				{
					Spline->ClearSplinePoints(); // clear the spline to avoid bad points
				
					for (const FVector& PointLocation : NavPath->PathPoints) // the NavPath was created and contains points to get people to a point
						{
						Spline->AddSplinePoint(PointLocation, ESplineCoordinateSpace::World); // how to add apoint to spline
					//DrawDebugSphere(GetWorld(), PointLocation, 8.f, 8, FColor::Green, false, 5.f); // for testing to see what is happening and points being created
						}
					CacheDestination = NavPath->PathPoints[NavPath->PathPoints.Num() - 1];
					bAutoRunning = true;
				}
			}
	
		FollowTime = 0.f; // this is within release so reset following and set bistargeting back to false
		bIsTargeting = false;
		}
	
}


/*
* code for responding to holding a input button down
*/
void AAuraPlayerController::AbilityInputTagHeld(FGameplayTag InputTag) 
{
	
	if(!InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB)) //checks if a LMB ability was used
	{
		if(GetAsc())
		{
			GetAsc()->AbilityInputTagHeld(InputTag);
		}
		return;
	}

	if(bIsTargeting || bSwiftKeyPressed) // checks if you are hovering over a enemy
	{
		if(GetAsc())
		{
			GetAsc()->AbilityInputTagHeld(InputTag);
		}
	}
	else // keeps location of clicked spot on map
	{
		FollowTime += GetWorld()->GetDeltaSeconds();
		
		if(CursorHit.bBlockingHit)
		{
			CacheDestination = CursorHit.ImpactPoint;
		}

		if(APawn* ControlledPawn = GetPawn())
		{
			const FVector WorldDirection = (CacheDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
			ControlledPawn->AddMovementInput(WorldDirection);
		}
		
	}
	
}

UAuraAbilitySystemComponent* AAuraPlayerController::GetAsc()
{
	if(AuraAbilitySystemComponent == nullptr)
	{
		AuraAbilitySystemComponent = Cast<UAuraAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}
	return AuraAbilitySystemComponent;
}

void AAuraPlayerController::AutoRun()
{

	if(!bAutoRunning) return;
	if(APawn* ControlledPawn = GetPawn())
	{
		const FVector LocationOnSpline = Spline->FindLocationClosestToWorldLocation(ControlledPawn->GetActorLocation(), ESplineCoordinateSpace::World); //get a location on the spline the player starts
		const FVector Direction = Spline->FindDirectionClosestToWorldLocation(LocationOnSpline, ESplineCoordinateSpace::World);
		const float DistanceToDestination = (LocationOnSpline - CacheDestination).Length(); // distance to where was cxlicked
		
		ControlledPawn->AddMovementInput(Direction);
	
		if(DistanceToDestination <= AutoRunAcceptanceRadius)
		{
			bAutoRunning = false;
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

void AAuraPlayerController::Swift(const FInputActionValue& InputActionValue)
{
	
	GEngine->AddOnScreenDebugMessage(1, 3.f, FColor::Green, TEXT("Swift Key pressed"));
}

void AAuraPlayerController::OpenMenu(const FInputActionValue& InputActionValue)
{
	bIsMenuOpen = true;
}

