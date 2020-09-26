// Copyright Raphael Hamzagic de Carvalho 2020


#include "ProjectileBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectileBase::OnHit);
	RootComponent = ProjectileMesh;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovement->InitialSpeed = MovementSpeed;
	ProjectileMovement->MaxSpeed = MovementSpeed;

	ParticleTrail = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle Trail"));
	ParticleTrail->SetupAttachment(RootComponent);

	InitialLifeSpan = 3.0f;
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), LaunchSound, GetActorLocation());
}

void AProjectileBase::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	AActor* ProjectileOwner = GetOwner();
	if (ProjectileOwner != nullptr)
	{
		if (OtherActor && OtherActor != this && OtherActor != ProjectileOwner)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticle, GetActorLocation());
			UGameplayStatics::ApplyDamage(OtherActor, Damage, ProjectileOwner->GetInstigatorController(), this, DamageType);
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), HitSound, GetActorLocation());
		}

		Destroy();
	}
}