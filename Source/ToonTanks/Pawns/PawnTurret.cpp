// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "PawnTank.h"

// Called when the game starts or when spawned
void APawnTurret::BeginPlay()
{
	Super::BeginPlay();

	/* Setting up the Timer */
	GetWorld()->GetTimerManager().SetTimer(
		FireRateTimerHandle, 
		this, 
		&APawnTurret::CheckFireCondition, 
		FireRate, 
		true
	);

	PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

// Called every frame
void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APawnTurret::CheckFireCondition()
{
	// If the Player is Valid and Alive
	if (!PlayerPawn)
	{
		return;
	}

	// If Player is in Range
	if (DistanceToPlayer() <= FireRange)
	{
		UE_LOG(LogTemp, Warning, TEXT("Fire!"))
	}
}

float APawnTurret::DistanceToPlayer()
{
	if (!PlayerPawn)
	{
		return 0.0f;
	}

	return FVector::Dist(PlayerPawn->GetActorLocation(), this->GetActorLocation());
}