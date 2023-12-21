
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "ShooterCharacterClass.generated.h"

class AGun;

UCLASS()
class MYFIRSTUESHOOTER_API AShooterCharacterClass : public ACharacter
{
	GENERATED_BODY() //must remain on line 12

public:
	AShooterCharacterClass();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	APlayerController* GetPlayerController();

	void SetupMappingContext();

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintPure)
	bool IsDead() const;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputMappingContext* MainMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* MoveForwardAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* MoveRightAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* FireAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* MouseTiltRightAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* MouseTiltUpAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* LookUpRateAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* LookRightRateAction;

	void MoveForward(const FInputActionValue& Value);

	void MoveRight(const FInputActionValue& Value);

	void Fire(const FInputActionValue& Value);

	void MouseTiltRight(const FInputActionValue& Value);

	void MouseTiltUp(const FInputActionValue& Value);

	void LookUpRate(const FInputActionValue& Value);

	void LookRightRate(const FInputActionValue& Value);

private:
	UPROPERTY(EditAnywhere, Category = "Components")
	class USpringArmComponent* SpringArm;
		
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCameraComponent* Camera;
	
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float Speed = 800.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float RotationRate = 10.f;	

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGun> GunClass;

	UPROPERTY()
	AGun* Gun;

	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 50.f;

	UPROPERTY(VisibleAnywhere)
	float CurrentHealth;
};
