// Copyright Raphael Hamzagic de Carvalho 2020

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "PawnTurret.generated.h"

class APawnTank;

UCLASS()
class TOONTANKS_API APawnTurret : public APawnBase
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float FireRate = 2.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float FireRange = 500.0f;
	FTimerHandle FireRateTimerHandle;
	void CheckFireCondition();

	APawnTank* PlayerPawn = nullptr;
	float ReturnDistanceToPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	APawnTurret();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
