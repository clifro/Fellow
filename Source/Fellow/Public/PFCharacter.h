// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Engine/DataTable.h"
#include "PFPlayerData.h"
#include "PFWeapon.h"
#include "Animation/AnimMontage.h"
#include "PFCharacter.generated.h"

UCLASS()
class FELLOW_API APFCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APFCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UDataTable* StatsTable;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UAnimMontage* HitMontage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FName CharacterName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float HitScanRange = 3000;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float Health;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FCharacterData CharacterData;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		APFWeapon* Weapon;

	UFUNCTION(BlueprintCallable)
		void Fire();

	UFUNCTION(BlueprintCallable)
		void DoJump();

	UFUNCTION(BlueprintCallable)
		void Move(float Direction);

	UFUNCTION(BlueprintNativeEvent, BlueprintPure)
		FVector GetAimDirection();

	UFUNCTION(BlueprintNativeEvent, BlueprintPure)
		FVector GetAimStartLocation();

	UFUNCTION(BlueprintCallable)
		void FireWeapon();

	UFUNCTION(BlueprintCallable)
		void ShowHitEffects(FHitResult HitResult);

	UFUNCTION(BlueprintCallable)
		void ApplyDamage(FHitResult HitResult);

	UFUNCTION()
		void ReceiveDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
};
