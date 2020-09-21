// Copyright Raphael Hamzagic de Carvalho 2020


#include "PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "PawnTank.h"

APawnTurret::APawnTurret()
{
}

// Called when the game starts or when spawned
void APawnTurret::BeginPlay()
{
	Super::BeginPlay();

	PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));

	GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true);
}

// Called every frame
void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerPawn != nullptr)
	{
		if (ReturnDistanceToPlayer() <= FireRange)
		{
			RotateTurret(PlayerPawn->GetActorLocation());
		}
	}
}

void APawnTurret::CheckFireCondition()
{
	if (PlayerPawn != nullptr)
	{
		if (ReturnDistanceToPlayer() <= FireRange)
		{
			Fire();
		}
	}		
}

float APawnTurret::ReturnDistanceToPlayer()
{
	float Distance = 0.f;
	if (PlayerPawn != nullptr)
	{
		Distance = FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation());
	}
	return Distance;
}

void APawnTurret::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}