

#include "ShooterCharacterClass.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/InputComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Gun.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MyFirstUEShooterGameModeBase.h"

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

    CurrentHealth = MaxHealth;
}

void AShooterCharacterClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AShooterCharacterClass::MoveForward(const FInputActionValue &Value)
{
    FVector CurrentValue;
    CurrentValue = Value.Get<FVector>();
    
    AddMovementInput(GetActorForwardVector() * CurrentValue.X);
    
}

void AShooterCharacterClass::MoveRight(const FInputActionValue &Value)
{
    FVector CurrentValue;
    CurrentValue = Value.Get<FVector>();
    AddMovementInput(GetActorRightVector() * CurrentValue.Y);
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

float AShooterCharacterClass::TakeDamage(float DamageAmount, FDamageEvent const &DamageEvent, AController *EventInstigator, AActor *DamageCauser)
{
    float DamageApplied = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
    
    DamageAmount = FMath::Min(DamageAmount, CurrentHealth);
    CurrentHealth -= DamageAmount;
    UE_LOG(LogTemp, Warning, TEXT("Current Health: %f"), CurrentHealth);

    if (IsDead())
    {
        AMyFirstUEShooterGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AMyFirstUEShooterGameModeBase>();
        if (GameMode != nullptr)
        {
            GameMode->PawnKilled(this);
        }
        DetachFromControllerPendingDestroy();
        GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    }
    return DamageApplied;
}

bool AShooterCharacterClass::IsDead() const
{
    return CurrentHealth <= 0;
}

float AShooterCharacterClass::GetHealthPercent() const
{
    return CurrentHealth / MaxHealth;
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
