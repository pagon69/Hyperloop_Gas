// all rights reserved, Copyright Alleyne Technologies

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"
#include "BTTask_Patrol.generated.h"

/**
 * 
 */
UCLASS()
class HYPERLOOP_API UBTTask_Patrol : public UBTTask_BlueprintBase
{
	GENERATED_BODY()
public:
	
protected:
	
private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	//virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	
};
