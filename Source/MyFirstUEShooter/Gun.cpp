// Fill out your copyright notice in the Description page of Project Settings.

#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Engine/DamageEvents.h"
#include "Sound/SoundBase.h"

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
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, MeshComponent, TEXT("MuzzleFlashSocket"));
	
	FHitResult HitResult;
	FVector ShotDirection;
	
	bool bLineTracing = GunTrace(HitResult, ShotDirection);
	if (bLineTracing)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitVFX, HitResult.Location, ShotDirection.Rotation(), true);
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, HitResult.Location, ShotDirection.Rotation(), true);

		AActor *HitedActor = HitResult.GetActor();
		if (HitedActor)
		{
			AController* OwnerController = GetOwnerController();
			if (OwnerController == nullptr) return;
			FPointDamageEvent DamageEvent(Damage, HitResult, ShotDirection, nullptr);
			HitedActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
		}
	}
}

bool AGun::GunTrace(FHitResult &HitResult, FVector& ShotDirection)
{
	AController* OwnerController = GetOwnerController();
	if (OwnerController == nullptr) return false;	
	FVector ViewPointLocation;
	FRotator ViewPointRotation;
	OwnerController->GetPlayerViewPoint(ViewPointLocation, ViewPointRotation);
	ShotDirection = -ViewPointRotation.Vector();
	FVector ViewPointEnd = ViewPointLocation + ViewPointRotation.Vector() * MaxRange;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());
	return GetWorld()->LineTraceSingleByChannel(HitResult, ViewPointLocation, ViewPointEnd, ECollisionChannel::ECC_GameTraceChannel1, Params);
}

AController *AGun::GetOwnerController() const
{
	APawn *OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr) return nullptr;	
	return OwnerPawn->GetController();
}
