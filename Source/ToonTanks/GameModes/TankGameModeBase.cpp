// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameModeBase.h"
#include "ToonTanks/Pawns/PawnTank.h"
#include "ToonTanks/Pawns/PawnTurret.h"
#include "Kismet/GameplayStatics.h"

void ATankGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// Call HandleGameStart() to initialise the start countdown, turret activation, pawn check etc.
	HandleGameStart();
}

void ATankGameModeBase::ActorDied(AActor* DeadActor)
{
	// Check what type of actor died. If turret, tally. If Player -> go to lose condition
	if (DeadActor == PlayerTank)
	{
		PlayerTank->HandleDestruction();
		HandleGameOver(false);
	}
	else if(APawnTurret* DestroyedTurret = Cast<APawnTurret>(DeadActor))
	{
		DestroyedTurret->HandleDestruction();
		TargetTurrets--;
		if (TargetTurrets <= 0)
		{
			HandleGameOver(true);
		}
	}
}

void ATankGameModeBase::HandleGameStart()
{
	// Initialise the start countdown, turret activation, pawn check etc.
	// Get reference and game win/lose conditions - Number of Turrets the player will have to kill
	TargetTurrets = GetTargetTurretCount();
	PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));

	// Call Blueprint version GameStart();
	GameStart();
}

void ATankGameModeBase::HandleGameOver(bool PlayerWon)
{
	// See if the player has destroyed all the turrets, show win result
	// else if Turret destroyed player, show lose result
	// Call blueprint version GameOver(bool)
	GameOver(PlayerWon);
}

int32 ATankGameModeBase::GetTargetTurretCount()
{
	TArray<AActor*> TurretActors;
	// Static Class means that we do not need to pass in a specific object of the class
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnTurret::StaticClass(), TurretActors);
	return TurretActors.Num();
}

