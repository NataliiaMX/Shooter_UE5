// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_Shoot.h"
#include "BrainComponent.h"
#include "AIController.h"
#include "ShooterCharacterClass.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

UBTTaskNode_Shoot::UBTTaskNode_Shoot()
{
    NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTaskNode_Shoot::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);
    
    if(OwnerComp.GetAIOwner() == nullptr)
    {
        return EBTNodeResult::Failed;
    }
    AShooterCharacterClass* Character = Cast<AShooterCharacterClass>(OwnerComp.GetAIOwner()->GetPawn());
    if(Character == nullptr)
    {
        return EBTNodeResult::Failed;
    }
    Character->Fire(true);

    return EBTNodeResult::Succeeded;
}
