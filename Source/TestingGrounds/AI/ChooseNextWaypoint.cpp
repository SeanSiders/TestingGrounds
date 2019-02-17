#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PatrolRoute.h"
#include "AIController.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    // get AI Controller
    auto AIController = OwnerComp.GetAIOwner();
    // get the controlled pawn from that controller
    auto ControlledPawn = AIController->GetPawn();
    // get the UPatrolRoute component on that pawn, which is assigned in blueprint
    auto PatrolRoute = ControlledPawn->FindComponentByClass<UPatrolRoute>();
    if (!ensure(PatrolRoute)) { return EBTNodeResult::Failed; }
    
    // get the array that contains the set patrol points
    auto PatrolPoints = PatrolRoute->GetPatrolPoints();
    if (PatrolPoints.Num() == 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("A guard has no patrol points"))
        EBTNodeResult::Failed;
    }
    
    // get reference to the blackboard created in UE editor
    auto BlackboardComp = OwnerComp.GetBlackboardComponent();
    // get first element in array for AI to move to
    auto Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
    // set the blackboard key that contains AI's next target point, this is specified by index of the TArray PatrolPoints
    BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[Index]);
    // mod the next index up by the total elements in the array to continue iteration through the scope of the array
    auto NextIndex = (Index +1) % PatrolPoints.Num();
    // set the next target point for AI to move to
    BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);
    
    return EBTNodeResult::Succeeded;
}
