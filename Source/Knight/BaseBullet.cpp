// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseBullet.h"

void ABaseBullet::BeginPlay() {
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(BeginTimerHandle, this, &ABaseBullet::Destroy, LifeTime);
}

void ABaseBullet::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);
}

void ABaseBullet::NotifyActorBeginOverlap(AActor * OtherActor)
{
	AKnightCharacter* KnightOwner = Cast<AKnightCharacter>(this->GetOwner());

	if (KnightOwner) {
		ABaseEnemyCharacter* Target = Cast<ABaseEnemyCharacter>(OtherActor);

		if (Target) {
			Target->DamageCharacter(DamagePoint);
		}

		return;
	}

	ABaseEnemyCharacter* EnemyOwner = Cast<ABaseEnemyCharacter>(this->GetOwner());

	if (EnemyOwner) {
		AKnightCharacter* Target = Cast<AKnightCharacter>(OtherActor);

		if (Target) {
			Target->DamageCharacter(DamagePoint);
		}

		return;
	}

	

	/*FVector LocationCharacter = Knight->GetActorLocation();
	FVector LocationLaunch = LaunchPoint->GetComponentLocation();
	FVector LaunchDirect = (LocationCharacter - LocationLaunch);
	LaunchDirect.Normalize();

	FVector LaunchImpulse = LaunchForce * LaunchDirect;
	Knight->LaunchCharacter(LaunchImpulse, false, false);*/
}
