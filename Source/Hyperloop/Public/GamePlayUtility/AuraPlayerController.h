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

	//the things needed for my custom enhanced input options
	void AbilityInputTagPress(FGameplayTag InputTag) ;
	void AbilityInputTagReleased(FGameplayTag InputTag) ;
	void AbilityInputTagHeld(FGameplayTag InputTag) ;

	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UAuraInputConfig> InputConfig;

	UPROPERTY()
	TObjectPtr<UAuraAbilitySystemComponent> AuraAbilitySystemComponent;

	UAuraAbilitySystemComponent* GetAsc();
	
};
