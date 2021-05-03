// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemyCharacter.h"

ABaseEnemyCharacter::ABaseEnemyCharacter() {

}

void ABaseEnemyCharacter::UpdateAnimState()
{

	if (IsWalk) {
		SetAnimState(WalkState);
	}

	if (IsFall) {
		SetAnimState(JumpState);
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

void ABaseEnemyCharacter::Attack()
{

}
