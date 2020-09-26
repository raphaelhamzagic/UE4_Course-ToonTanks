// Copyright Raphael Hamzagic de Carvalho 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TankGameModeBase.generated.h"

class APawnTank;
class APawnTurret;
class APlayerControllerBase;

UCLASS()
class TOONTANKS_API ATankGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

private: 
	APawnTank* PlayerTank;
	APlayerControllerBase* PlayerController = nullptr;

	int TargetTurrets = 0;
	int GetTargetTurretCount();

	void HandleGameStart();
	void HandleGameOver(bool PlayerWon);

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void GameStart();
	
	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool PlayerWon);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Geme Loop")
	int StartDelay = 3;

public:
	void ActorDied(AActor* DeadActor);
};
