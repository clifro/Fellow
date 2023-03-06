// Fill out your copyright notice in the Description page of Project Settings.

#include "PFCharacter.h"
#include "Logger.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AISense_Damage.h"
#include "Perception/AISense_Hearing.h"
#include "Components/StaticMeshComponent.h"
// Sets default values
APFCharacter::APFCharacter()
{
	
}

// Called when the game starts or when spawned
void APFCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (StatsTable)
	{
		FCharacterData* characterTableData = StatsTable->FindRow<FCharacterData>(CharacterName, "");

		if (characterTableData)
		{
			CharacterData = *characterTableData;

			if (GetCharacterMovement())
			{
				GetCharacterMovement()->MaxWalkSpeed = CharacterData.Stats.WalkSpeed;
				GetCharacterMovement()->JumpZVelocity = CharacterData.Stats.JumpSpeed;
				GetCharacterMovement()->MaxWalkSpeedCrouched = CharacterData.Stats.CrouchSpeed;
				Health = CharacterData.Stats.Health;

				if (OnHealthUpdated.IsBound())
					OnHealthUpdated.Broadcast(Health, CharacterData.Stats.Health);
			}
		}
	}

	if (CharacterData.Weapons.Weapon)
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.Owner = this;
		Weapon = GetWorld()->SpawnActor<APFWeapon>(CharacterData.Weapons.Weapon->GetDefaultObject()->GetClass(), FTransform::Identity, SpawnInfo);

		if (Weapon && GetMesh())
		{
			FAttachmentTransformRules AttachmentRules(EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, false);
			Weapon->AttachToComponent(GetMesh(), AttachmentRules, CharacterData.Weapons.SocketName);
			Weapon->Character = this;
		}
	}

	OnTakeAnyDamage.AddDynamic(this, &APFCharacter::ReceiveDamage);
}

// Called every frame
void APFCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APFCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APFCharacter::Fire()
{
	
}

void APFCharacter::DoJump()
{
	Jump();
}

void APFCharacter::Move(float Direction)
{

}

// Overridden in respective Character BP
FVector APFCharacter::GetAimDirection_Implementation()
{
	return GetActorForwardVector();
}

// Overridden in respective Character BP
FVector APFCharacter::GetAimStartLocation_Implementation()
{
	return GetActorLocation();
}

void APFCharacter::FireWeapon()
{
	if (IsAlive() && Weapon)
	{
		FVector EndLocation = GetAimStartLocation() + GetAimDirection() * HitScanRange;
		FHitResult HitResult;
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(this);
		QueryParams.bReturnPhysicalMaterial = true;
		GetWorld()->LineTraceSingleByChannel(HitResult, GetAimStartLocation(), EndLocation, ECollisionChannel::ECC_Visibility, QueryParams);
		//DrawDebugLine(GetWorld(), GetAimStartLocation(), EndLocation, HitResult.bBlockingHit ? FColor::Blue : FColor::Red, false, 5.0f, 0, 1.0f);
		Weapon->PlayFX();
		UAISense_Hearing::ReportNoiseEvent(GetWorld(), GetActorLocation(), 100, this, 4000, "");

		if (HitResult.bBlockingHit) 
		{
			ShowHitEffects(HitResult);
			ApplyDamage(HitResult);
		}	
	}
}

void APFCharacter::ShowHitEffects(FHitResult HitResult)
{
	if (HitResult.bBlockingHit && HitResult.GetActor())
	{
		AActor* hitActor = HitResult.GetActor();
		APFCharacter* character = Cast<APFCharacter>(hitActor);

		if (character == nullptr)
		{
			if (hitActor->IsRootComponentMovable())
			{
				UStaticMeshComponent* MeshComponent = Cast<UStaticMeshComponent>(hitActor->GetRootComponent());

				if (MeshComponent)
				{
					MeshComponent->AddForce(GetAimDirection() * 100000 * MeshComponent->GetMass());
				}
			}
		}

		PlayHitFX(HitResult);
	}
}

void APFCharacter::ApplyDamage(FHitResult HitResult)
{
	AActor* hitActor = HitResult.GetActor();

	if (HitResult.bBlockingHit && hitActor)
	{
		APFCharacter* character = Cast<APFCharacter>(hitActor);
		if (character)
		{
			if (HitResult.BoneName == "head")
				UGameplayStatics::ApplyDamage(character, CharacterData.Weapons.Damage * 1000, GetController(), this, nullptr);
			else
			{
				UAISense_Damage::ReportDamageEvent(GetWorld(), character, this, CharacterData.Weapons.Damage, GetActorLocation(), HitResult.ImpactPoint);
				UGameplayStatics::ApplyDamage(character, CharacterData.Weapons.Damage, GetController(), this, nullptr);
			}
		}
	}
}

void APFCharacter::ReceiveDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	if (Health > 0)
	{
		Health -= Damage;

		if (OnHealthUpdated.IsBound())
			OnHealthUpdated.Broadcast(Health, CharacterData.Stats.Health);

		if (Health <= 0)
		{
			if (GetMesh())
				GetMesh()->SetSimulatePhysics(true);
		}
		else
		{
			if (GetMesh() && GetMesh()->GetAnimInstance())
			{
				GetMesh()->GetAnimInstance()->Montage_Play(HitMontage);
			}
		}
	}
}

void APFCharacter::AddHealth(float HealthToAdd)
{
	Health += HealthToAdd;
	FMath::Clamp(Health, 0, CharacterData.Stats.Health);

	if (OnHealthUpdated.IsBound())
		OnHealthUpdated.Broadcast(Health, CharacterData.Stats.Health);
}