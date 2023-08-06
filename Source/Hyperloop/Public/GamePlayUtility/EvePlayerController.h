// all rights reserved, Copyright Alleyne Technologies

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EvePlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class IMouseTargetInterface;

/**
 * 
 */

UCLASS()
class HYPERLOOP_API AEvePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AEvePlayerController();
	
protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	virtual void PlayerTick(float DeltaTime) override;
	
private:

	UPROPERTY(EditAnywhere, Category= "Input")
	TObjectPtr<UInputMappingContext> EveContext;


	UPROPERTY(EditAnywhere, Category= "Input")
	TObjectPtr<UInputAction> MoveAction;

	void Move(const FInputActionValue& InputActionValue) ;

	void CursorTrace();

	//used to track the things under the cursor current and next actor
	TObjectPtr<IMouseTargetInterface> LastActor;
	TObjectPtr<IMouseTargetInterface> ThisActor;
	
};
