// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"


void AShooterAIController::BeginPlay()
{
    Super::BeginPlay();

}

void AShooterAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    FollowPlayer();
}

void AShooterAIController::FollowPlayer()
{
    APawn* Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if(LineOfSightTo(Player))
    {
        SetFocus(Player);
        MoveToActor(Player, AggroRadius, true, true);
    }
    else
    {
        ClearFocus(EAIFocusPriority::Gameplay);
        StopMovement();
    }
}