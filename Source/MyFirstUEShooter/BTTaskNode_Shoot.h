// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_Shoot.generated.h"

/**
 * 
 */
UCLASS()
class MYFIRSTUESHOOTER_API UBTTaskNode_Shoot : public UBTTaskNode
{
	GENERATED_BODY() //line 15

public:
	UBTTaskNode_Shoot();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) override;
	
};
