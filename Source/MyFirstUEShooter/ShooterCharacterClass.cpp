// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacterClass.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"

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

void AShooterCharacterClass::Move(const FInputActionValue &Value)
{
    FVector2D CurrentValue = Value.Get<FVector2D>();
    FVector Offset3D(CurrentValue.X, CurrentValue.Y, 0.0f);
    float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
    FVector DeltaLocation = Offset3D * Speed * DeltaTime;
    bool DoesSweep = true;
    AddActorLocalOffset(DeltaLocation, DoesSweep);
    
    // FRotator DeltaRotation = FRotator::ZeroRotator;
    // DeltaRotation.Yaw = CurrentValue.Y * TurnRate * DeltaTime;  
    // AddActorLocalRotation(DeltaRotation, DoesSweep);
}

void AShooterCharacterClass::Fire(const FInputActionValue &Value)
{
    UE_LOG(LogTemp, Display, TEXT("Fire"));
}

void AShooterCharacterClass::MouseTilt(const FInputActionValue &Value)
{
    UE_LOG(LogTemp, Display, TEXT("Mouse tilt"));
}

// Called every frame
void AShooterCharacterClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

APlayerController* AShooterCharacterClass::GetPlayerController()
{
    APlayerController* PlayerController = Cast<APlayerController>(Controller);
    return PlayerController;
}

void AShooterCharacterClass::SetupMappingContext()
{
    if(GetPlayerController())
    {
        UEnhancedInputLocalPlayerSubsystem* Subsystem = 
                    ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetPlayerController()->GetLocalPlayer());
        if(Subsystem)
        {
            Subsystem->AddMappingContext(MainMappingContext, 0);
        }
    }
}

void AShooterCharacterClass::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	SetupMappingContext();
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if(UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AShooterCharacterClass::Move);
        EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &AShooterCharacterClass::Fire);
        EnhancedInputComponent->BindAction(MouseTiltAction, ETriggerEvent::Triggered, this, &AShooterCharacterClass::MouseTilt);
    }
}
