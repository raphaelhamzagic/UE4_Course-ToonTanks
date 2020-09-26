// Copyright Raphael Hamzagic de Carvalho 2020


#include "TankGameModeBase.h"
#include "ToonTanks/Pawns/PawnTank.h"
#include "ToonTanks/Pawns/PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanks/PlayerControllers/PlayerControllerBase.h"

void ATankGameModeBase::BeginPlay()
{
    Super::BeginPlay();
    HandleGameStart();
}

void ATankGameModeBase::ActorDied(AActor* DeadActor)
{
    UE_LOG(LogTemp, Warning, TEXT("A Pawn Died."));
    if (DeadActor == PlayerTank)
    {
        PlayerTank->HandleDestruction();
        HandleGameOver(false);
        if (PlayerController != nullptr)
        {
            PlayerController->SetPlayerEnabledState(false);
        }
    }
    else if (APawnTurret* DestroyedTurret = Cast<APawnTurret>(DeadActor))
    {
        DestroyedTurret->HandleDestruction();
        if (--TargetTurrets == 0)
        {
            HandleGameOver(true);
        }
    }
}

void ATankGameModeBase::HandleGameStart()
{
    TargetTurrets = GetTargetTurretCount();
    PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
    PlayerController = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
    GameStart();
    if (PlayerController != nullptr)
    {
        PlayerController->SetPlayerEnabledState(false);
        FTimerHandle PlayerEnableHandle;
        FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(
            PlayerController,
            &APlayerControllerBase::SetPlayerEnabledState,
            true
        );
        GetWorld()->GetTimerManager().SetTimer(
            PlayerEnableHandle,
            PlayerEnableDelegate,
            (float) StartDelay,
            false
        );
    }
}

void ATankGameModeBase::HandleGameOver(bool PlayerWon)
{
    GameOver(PlayerWon);
}

int ATankGameModeBase::GetTargetTurretCount()
{
    TArray<AActor*> TurretActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnTurret::StaticClass(), TurretActors);
    return TurretActors.Num();
}