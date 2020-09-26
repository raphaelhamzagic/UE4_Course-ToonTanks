// Copyright Raphael Hamzagic de Carvalho 2020


#include "HealthComponent.h"
#include "ToonTanks/GameModes/TankGameModeBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	Health = DefaultHealth;
	GameMode = Cast<ATankGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
}


void UHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage != 0 && Health > 0)
	{
		Health = FMath::Clamp(Health - Damage, 0.f, DefaultHealth);

		if (Health <= 0)
		{
			if (GameMode != nullptr)
			{
				GameMode->ActorDied(GetOwner());
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("GameMode reference is not set."));
			}
		}
	}
}

