// Fill out your copyright notice in the Description page of Project Settings.


#include "PFWeapon.h"
#include "Logger.h"

// Sets default values
APFWeapon::APFWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APFWeapon::BeginPlay()
{
	Super::BeginPlay();

	WeaponMesh = Cast<USkeletalMeshComponent>(GetComponentByClass(USkeletalMeshComponent::StaticClass()));
}

// Called every frame
void APFWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APFWeapon::Fire(FVector StartLocation, FVector Direction)
{

}

void APFWeapon::PlayFX()
{

}

