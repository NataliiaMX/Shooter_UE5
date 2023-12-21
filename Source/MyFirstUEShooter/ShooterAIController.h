// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ShooterAIController.generated.h"

class UBehaviorTree;


UCLASS()
class MYFIRSTUESHOOTER_API AShooterAIController : public AAIController
{
	GENERATED_BODY() //must remain on line 15
	
	public:
		virtual void Tick(float DeltaTime) override;
	protected:
		virtual void BeginPlay() override;

	private:
		UPROPERTY(EditAnywhere)
		UBehaviorTree* AIBehavior;

		void FollowPlayer();

		void SetupBehaviorTree();
};
