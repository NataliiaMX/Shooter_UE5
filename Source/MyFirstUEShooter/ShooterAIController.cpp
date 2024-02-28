// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ShooterCharacterClass.h"


void AShooterAIController::BeginPlay()
{
    Super::BeginPlay();
    
    SetupBehaviorTree();
}

void AShooterAIController::SetupBehaviorTree()
{
    if(AIBehavior)
    {
        RunBehaviorTree(AIBehavior);

        APawn* Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
        
        GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
    }
}

void AShooterAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

 
}

bool AShooterAIController::IsDead() const
{
    AShooterCharacterClass* ControlledCharacter = Cast<AShooterCharacterClass>(GetPawn());
    if(ControlledCharacter != nullptr)
    {
        return ControlledCharacter->IsDead();
    }
    return true;
}
