// Fill out your copyright notice in the Description page of Project Settings.

#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Engine/DamageEvents.h"
 
AGun::AGun()
{
	PrimaryActorTick.bCanEverTick = true;

	GunRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = GunRootComponent;

	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetupAttachment(GunRootComponent);
}

void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::Shoot()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlashVFX, MeshComponent, TEXT("MuzzleFlashSocket"));

	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if(OwnerPawn)
	{
		AController* OwnerController = OwnerPawn->GetController();
		if(OwnerController)
		{
			FVector ViewPointLocation;
			FRotator ViewPointRotation;
			OwnerController->GetPlayerViewPoint(ViewPointLocation, ViewPointRotation);
			
			FVector ViewPointEnd = ViewPointLocation + ViewPointRotation.Vector() * MaxRange;

			
			FHitResult HitResult;
			bool bLineTracing = GetWorld()->LineTraceSingleByChannel(HitResult, ViewPointLocation, ViewPointEnd, ECollisionChannel::ECC_GameTraceChannel1);
			if(bLineTracing)
			{
				FVector ShotDirection = -ViewPointRotation.Vector();
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitVFX, HitResult.Location, ShotDirection.Rotation(), true);

				
				AActor* HitedActor = HitResult.GetActor();
				if(HitedActor)
				{
					FPointDamageEvent DamageEvent(Damage, HitResult, ShotDirection, nullptr);
					HitedActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
				}
			}
		}
	}
}
