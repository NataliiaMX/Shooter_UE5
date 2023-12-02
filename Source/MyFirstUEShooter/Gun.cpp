// Fill out your copyright notice in the Description page of Project Settings.

#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
 
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
	UE_LOG(LogTemp, Warning, TEXT("Shoot"));
}
