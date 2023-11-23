

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacterClass.generated.h"

UCLASS()
class MYFIRSTUESHOOTER_API AShooterCharacterClass : public ACharacter
{
	GENERATED_BODY() //must remain on line 12

public:
	AShooterCharacterClass();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
