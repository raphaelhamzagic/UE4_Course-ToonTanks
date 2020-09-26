// Copyright Raphael Hamzagic de Carvalho 2020

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "PawnTank.generated.h"

class USpringArmComponent;
class UCameraComponent;
UCLASS()
class TOONTANKS_API APawnTank : public APawnBase
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float MoveSpeed = 100.f;

	FVector MoveDirection;
	void CalculateMoveInput(float Value);
	void Move();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float RotateSpeed = 100.f;

	FQuat RotationDirection;
	void CalculateRotateInput(float Value);
	void Rotate();

	APlayerController* PlayerController = nullptr;
	bool bIsPlayerAlive = true;

public:
	APawnTank();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void HandleDestruction() override;

	bool GetIsPlayerAlive();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
