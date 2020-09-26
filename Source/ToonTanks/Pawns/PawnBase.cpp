// Copyright Raphael Hamzagic de Carvalho 2020


#include "PawnBase.h"
#include "Components/CapsuleComponent.h"
#include "ToonTanks/Actors/ProjectileBase.h"
#include "ToonTanks/Components/HealthComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APawnBase::APawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = Capsule;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(RootComponent);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}

void APawnBase::RotateTurret(FVector LookAtTarget)
{
	FVector LookAt = FVector(LookAtTarget.X, LookAtTarget.Y, TurretMesh->GetComponentLocation().Z);
	FVector StartLocation = TurretMesh->GetComponentLocation();
	FRotator TurretRotation = FVector(LookAt - StartLocation).Rotation();
	TurretMesh->SetWorldRotation(TurretRotation);
}

void APawnBase::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("Fire!"));
	if (ProjectileClass != nullptr)
	{
		// FVector ProjectilePosition = ProjectileSpawnPoint->GetComponentLocation();
		// FRotator ProjectileRotation = ProjectileSpawnPoint->GetComponentRotation();
		// AProjectileBase* TempProjectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass, ProjectilePosition, ProjectileRotation);
		AProjectileBase* TempProjectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass, ProjectileSpawnPoint->GetComponentTransform());
		TempProjectile->SetOwner(this);
	}
}

void APawnBase::HandleDestruction()
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DeathParticle, GetActorLocation());
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), DeathSound, GetActorLocation());
}