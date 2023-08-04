// all rights reserved, Copyright Alleyne Technologies

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EvePlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
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
	
private:

	UPROPERTY(EditAnywhere, Category= "Input")
	TObjectPtr<UInputMappingContext> EveContext;


	UPROPERTY(EditAnywhere, Category= "Input")
	TObjectPtr<UInputAction> MoveAction;

	void Move(const FInputActionValue& InputActionValue);
	
};
