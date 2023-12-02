

#include "ShooterCharacterClass.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Gun.h"


AShooterCharacterClass::AShooterCharacterClass()
{
	PrimaryActorTick.bCanEverTick = true;

    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArm->SetupAttachment(RootComponent);

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);
}

void AShooterCharacterClass::BeginPlay()
{
	Super::BeginPlay();
	
    GetMesh()->HideBoneByName(TEXT("weapon_l"), EPhysBodyOp::PBO_None);
    GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);

    Gun = GetWorld()->SpawnActor<AGun>(GunClass);
    Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
    Gun->SetOwner(this);
}

void AShooterCharacterClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AShooterCharacterClass::MoveForward(const FInputActionValue &Value)
{
    FVector CurrentValue;
    CurrentValue = Value.Get<FVector>();
    AddMovementInput(GetActorForwardVector() * CurrentValue.X * Speed);
    
}

void AShooterCharacterClass::MoveRight(const FInputActionValue &Value)
{
    FVector CurrentValue;
    CurrentValue = Value.Get<FVector>();
    AddMovementInput(GetActorRightVector() * CurrentValue.Y * Speed);
}

void AShooterCharacterClass::Fire(const FInputActionValue &Value)
{
    Gun->Shoot();
}

void AShooterCharacterClass::MouseTiltRight(const FInputActionValue &Value)
{
    float ValueToFloat = Value.GetMagnitude();
    AddControllerYawInput(ValueToFloat);
}

void AShooterCharacterClass::MouseTiltUp(const FInputActionValue &Value)
{
    float ValueToFloat = Value.GetMagnitude();
    AddControllerPitchInput(-ValueToFloat);
}

void AShooterCharacterClass::LookUpRate(const FInputActionValue &Value)
{
    float ValueToFloat = Value.GetMagnitude();
    AddControllerPitchInput(ValueToFloat * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacterClass::LookRightRate(const FInputActionValue &Value)
{
    float ValueToFloat = Value.GetMagnitude();
    AddControllerYawInput(ValueToFloat * RotationRate * GetWorld()->GetDeltaSeconds());
}

//input management
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
        EnhancedInputComponent->BindAction(MoveForwardAction, ETriggerEvent::Triggered, this, &AShooterCharacterClass::MoveForward);
        EnhancedInputComponent->BindAction(MoveRightAction, ETriggerEvent::Triggered, this, &AShooterCharacterClass::MoveRight);
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
        EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &AShooterCharacterClass::Fire);
        EnhancedInputComponent->BindAction(MouseTiltRightAction, ETriggerEvent::Triggered, this, &AShooterCharacterClass::MouseTiltRight);
        EnhancedInputComponent->BindAction(MouseTiltUpAction, ETriggerEvent::Triggered, this, &AShooterCharacterClass::MouseTiltUp);
        EnhancedInputComponent->BindAction(LookUpRateAction, ETriggerEvent::Triggered, this, &AShooterCharacterClass::LookUpRate);
        EnhancedInputComponent->BindAction(LookRightRateAction, ETriggerEvent::Triggered, this, &AShooterCharacterClass::LookRightRate);
    } 
}
