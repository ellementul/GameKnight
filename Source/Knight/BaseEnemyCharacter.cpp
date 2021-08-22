// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemyCharacter.h"

void ABaseEnemyCharacter::UpdateAnimState()
{

	if (IsWalk) {
		SetAnimState(WalkState);
	}

	if (IsFall) {
		SetAnimState(JumpState);
	}

	if (IsSpeak) {
		SetAnimState(SpeakState);
	}
}

bool ABaseEnemyCharacter::IsIdle()
{
	return !(IsWalk || IsFall);
}

bool ABaseEnemyCharacter::Damaged(int Damage)
{
	int OldHealth = Health;

	Health -= Damage;

	return (Health != OldHealth);
}

void ABaseEnemyCharacter::Attack(FVector Target = FVector::ZeroVector)
{
	FVector BeginLocation = DirAttack->GetComponentLocation();
	ILaunchAimInterface* Bullet = Cast<ILaunchAimInterface>(SpawnBullet(BeginLocation));

	if (!Target.IsZero() && Bullet) {
		Bullet->LaunchAim(Target);
	}

}
