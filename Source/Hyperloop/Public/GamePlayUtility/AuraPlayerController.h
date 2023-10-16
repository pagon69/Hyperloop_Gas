// all rights reserved, Copyright Alleyne Technologies

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"

class UAuraInputConfig;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class IMouseTargetInterface;
class UAuraAbilitySystemComponent;
class USplineComponent;

/**
 * 
 */
UCLASS()
class HYPERLOOP_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AAuraPlayerController();
	
protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;
	
	virtual void PlayerTick(float DeltaTime) override;
	
private:

	UPROPERTY(EditAnywhere, Category= "Input")
	TObjectPtr<UInputMappingContext> AuraContext;

	UPROPERTY(EditAnywhere, Category= "Input")
	TObjectPtr<UInputAction> MoveAction;

	void Move(const FInputActionValue& InputActionValue);

	void CursorTrace();

	//used to track the things under the cursor current and next actor
	IMouseTargetInterface* LastActor;
	IMouseTargetInterface* ThisActor;

	FHitResult CursorHit;

	//the things needed for my custom enhanced input options
	void AbilityInputTagPress(FGameplayTag InputTag) ;
	void AbilityInputTagReleased(FGameplayTag InputTag) ;
	void AbilityInputTagHeld(FGameplayTag InputTag) ;

	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UAuraInputConfig> InputConfig;

	UPROPERTY()
	TObjectPtr<UAuraAbilitySystemComponent> AuraAbilitySystemComponent;

	UAuraAbilitySystemComponent* GetAsc();

	/**
	 * Below are the variables needed for click to move code that replicates
	 */
	//mouse click and move to variables -
	FVector CacheDestination = FVector::ZeroVector; //after you click on a spot in the world save it
	float FollowTime = 0.f; 
	float ShortPressThreshold = 0.5f; // how long you held the button down
	bool bAutoRunning = false; // if you are moving to the path of the last click 
	bool bIsTargeting = false;
	
	UPROPERTY(EditDefaultsOnly)
	float AutoRunAcceptanceRadius = 50.f;  // minimum distance for auto move to kick in

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USplineComponent> Spline; // needed to smooth out the pathing from player to click
	
	void AutoRun();
	
};
