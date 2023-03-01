// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "PFWeapon.h"
#include "PFPlayerData.generated.h"

USTRUCT(Blueprintable)
struct FCharacterStats
{
	GENERATED_BODY()

public: 

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float Health;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float WalkSpeed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float RunSpeed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float JumpSpeed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float CrouchSpeed;
};

USTRUCT(Blueprintable)
struct FWeaponData
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FName SocketName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSubclassOf<APFWeapon> Weapon;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float Damage = 200;
};

USTRUCT(Blueprintable)
struct FCharacterData : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FCharacterStats Stats;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FWeaponData Weapons;
};
