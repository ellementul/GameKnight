// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyKnigtCharacter.h"

AEnemyKnigtCharacter::AEnemyKnigtCharacter()
{
	CheckHitEnemyCollision = CreateDefaultSubobject<USphereComponent>(TEXT("CheckHitEnemyCollision"));
	CheckHitEnemyCollision->SetupAttachment(GetSprite());
}

bool AEnemyKnigtCharacter::CheckHitEnemy()
{
	TArray<AActor*> OverlappingActors;

	CheckHitEnemyCollision->GetOverlappingActors(OverlappingActors, EnemyClass);

	return !!OverlappingActors.Num();
}
