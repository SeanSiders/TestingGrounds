#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "ChooseNextWaypoint.generated.h"

/**
 * Logic for the AI to keep a list of patrolling waypoints and the next waypoint to move to
 */
UCLASS()
class TESTINGGROUNDS_API UChooseNextWaypoint : public UBTTaskNode
{
    GENERATED_BODY()
    
private:
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
    
protected:
    UPROPERTY(EditAnywhere, Category = "Blackboard")
    struct FBlackboardKeySelector IndexKey;
    
    UPROPERTY(EditAnywhere, Category = "Blackboard")
    struct FBlackboardKeySelector WaypointKey;
};
