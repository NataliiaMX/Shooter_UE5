
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "ShooterCharacterClass.generated.h"

UCLASS()
class MYFIRSTUESHOOTER_API AShooterCharacterClass : public ACharacter
{
	GENERATED_BODY() //must remain on line 12

public:
	AShooterCharacterClass();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputMappingContext* MainMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* FireAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* MouseTiltRightAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* MouseTiltUpAction;

	void Move(const FInputActionValue& Value);

	void Fire(const FInputActionValue& Value);

	void MouseTiltRight(const FInputActionValue& Value);

	void MouseTiltUp(const FInputActionValue& Value);

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	APlayerController* GetPlayerController();

	void SetupMappingContext();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float Speed = 200.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float TurnRate = 100.f;	
};
