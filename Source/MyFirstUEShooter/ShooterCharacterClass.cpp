// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacterClass.h"

// Sets default values
AShooterCharacterClass::AShooterCharacterClass()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShooterCharacterClass::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShooterCharacterClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterCharacterClass::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

