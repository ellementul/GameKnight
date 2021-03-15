// Fill out your copyright notice in the Description page of Project Settings.


#include "Trap.h"

void ATrap::NotifyHit(UPrimitiveComponent * MyComp, AActor * Other, UPrimitiveComponent * OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult & Hit)
{
	AKnightCharacter* Knight = Cast<AKnightCharacter>(Other);

	if (Knight) {
		Knight->DamageCharacter(DamagePoint);
		FVector LaunchImpulse = (-1) * LaunchForce * HitNormal;
		Knight->LaunchCharacter(LaunchImpulse, false, false);
	}
}
