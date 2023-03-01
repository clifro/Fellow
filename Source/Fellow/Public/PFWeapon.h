// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/SkeletalMesh.h"
#include "PFWeapon.generated.h"

UCLASS(Blueprintable)
class FELLOW_API APFWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APFWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		AActor* Character;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FName MuzzleSocketName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float HitScanRange;

	UFUNCTION(BlueprintCallable)
		void Fire(FVector StartLocation, FVector Direction);

	UFUNCTION(BlueprintCallable)
		void PlayFX();
};
