// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseBullet.h"

ABaseBullet::ABaseBullet() {
	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));

	if(IsGravity)
		Movement->ProjectileGravityScale = OneTileSpeed;
	else
		Movement->ProjectileGravityScale = 0;
}

void ABaseBullet::BeginPlay() {
	Movement->SetVelocityInLocalSpace(FVector(Speed * OneTileSpeed, 0, 0));

	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(BeginTimerHandle, this, &ABaseBullet::DestroyBullet, LifeTime);
}

void ABaseBullet::DestroyBullet() {
	this->Destroy();
}

void ABaseBullet::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);
}

void ABaseBullet::LaunchAim(FVector Target) {
	FVector SraightTrace = Target - GetActorLocation();
	float HorizontalSpeed = Speed * OneTileSpeed;
	float HalfOfFlyTime = SraightTrace.GetAbs().X / (HorizontalSpeed * 2);
	float VerticalSpeed = HalfOfFlyTime * OneTileSpeed;
	Movement->SetVelocityInLocalSpace(FVector(HorizontalSpeed, 0, VerticalSpeed));
}

void ABaseBullet::NotifyActorBeginOverlap(AActor * OtherActor)
{
	AKnightCharacter* KnightOwner = Cast<AKnightCharacter>(this->GetOwner());

	FVector LaunchDirect = FVector(GetVelocity().GetSignVector().X, 0, 1);

	FVector LaunchImpulse = LaunchForce * LaunchDirect;

	if (KnightOwner) {
		ABaseEnemyCharacter* Target = Cast<ABaseEnemyCharacter>(OtherActor);

		if (Target) {
			Target->DamageCharacter(DamagePoint);
			Target->LaunchCharacter(LaunchImpulse, false, false);
		}

		return;
	}

	ABaseEnemyCharacter* EnemyOwner = Cast<ABaseEnemyCharacter>(this->GetOwner());

	if (EnemyOwner) {
		AKnightCharacter* Target = Cast<AKnightCharacter>(OtherActor);

		if (Target) {
			Target->DamageCharacter(DamagePoint);
			Target->LaunchCharacter(LaunchImpulse, false, false);
		}

		return;
	}
}
