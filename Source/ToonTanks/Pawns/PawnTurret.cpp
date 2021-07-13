// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTurret.h"

// Called when the game starts or when spawned
void APawnTurret::BeginPlay()
{
	Super::BeginPlay();

	/* Setting up the Timer */
		// FTimerHandle
		// Current Object
		// Function to be called
		// FireRate, Timer rate
		// Should the Timer loop?
	GetWorld()->GetTimerManager().SetTimer(
		FireRateTimerHandle, 
		this, 
		&APawnTurret::CheckFireCondition, 
		FireRate, 
		true
	);
}

// Called every frame
void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APawnTurret::CheckFireCondition()
{
	// If the Player is Valid and Alive

	// If Player is in Range

	UE_LOG(LogTemp, Warning, TEXT("Fire!"))
}