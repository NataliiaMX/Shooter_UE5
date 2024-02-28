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

	UPROPERTY(EditAnywhere)
	UParticleSystem* MuzzleFlashVFX;

	UPROPERTY(EditAnywhere)
	UParticleSystem* HitVFX;

	UPROPERTY(EditAnywhere)
	float MaxRange = 1000.f;

	UPROPERTY(EditAnywhere)
	float Damage = 10.f;

	UPROPERTY(EditAnywhere)
	class USoundBase* MuzzleSound;

	UPROPERTY(EditAnywhere)
	class USoundBase* ImpactSound;

	bool GunTrace(FHitResult& HitResult, FVector& ShotDirection);

	AController* GetOwnerController() const;
};
