// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnBase.h"

#include "Components/CapsuleComponent.h"
#include "Math/UnrealMathUtility.h"
#include "ToonTanks/Actors/ProjectileBase.h"

// Sets default values
APawnBase::APawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// UE4 will automatically declare the first component to be the root component
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	// Initialize BaseMesh and make it a child of CapsuleComp
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(RootComponent);

	// We want the Turret to attach to the Base Mesh
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);

}

void APawnBase::RotateTurret(FVector LookAtTarget)
{
	// We dont want to let the camera rotate up or down, just on the X-Y plane
	FVector RotateAroundZAxis = FVector(LookAtTarget.X, LookAtTarget.Y, TurretMesh->GetComponentLocation().Z);
	FVector StartLocation = TurretMesh->GetComponentLocation();

	FRotator TurretRotation = FVector(RotateAroundZAxis - StartLocation).Rotation();

	TurretMesh->SetWorldRotation(TurretRotation);	
}

void APawnBase::Fire()
{
	if (ensure(ProjectileClass))
	{
		FVector ProjectileSpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
		FRotator ProjectileSpawnRotation = ProjectileSpawnPoint->GetComponentRotation();

		AProjectileBase* TempProjectile = GetWorld()->SpawnActor<AProjectileBase>(
			ProjectileClass, 
			ProjectileSpawnLocation, 
			ProjectileSpawnRotation
		);

		TempProjectile->SetOwner(this);
	}
}

void APawnBase::HandleDestruction()
{
	// --- Universal functionality --- 
	// Play death effects particle, sound and camera shake. 

	// --- Then do Child overrides ---
	// -- PawnTurret - Inform GameMode Turret died -> Then Destroy() self. 

	// -- PawnTank - Inform GameMode Player died -> Then Hide() all components && stop movement input.

}

