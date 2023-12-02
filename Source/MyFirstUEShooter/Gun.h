// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class MYFIRSTUESHOOTER_API AGun : public AActor
{
	GENERATED_BODY() //must remain on line 12
	
public:	
	AGun();

protected:
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Shoot();

private:
	UPROPERTY(VisibleAnywhere)
	class USceneComponent* GunRootComponent;

	UPROPERTY(VisibleAnywhere)
	class USkeletalMeshComponent* MeshComponent;
};
