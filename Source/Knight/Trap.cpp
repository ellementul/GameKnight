// Fill out your copyright notice in the Description page of Project Settings.


#include "Trap.h"

ATrap::ATrap()
{
	LaunchPoint = CreateDefaultSubobject<USceneComponent>(TEXT("LaunchPoint"));
	LaunchPoint->SetupAttachment(RootComponent);
}

void ATrap::NotifyActorBeginOverlap(AActor* OtherActor)
{
	AKnightCharacter* Knight = Cast<AKnightCharacter>(OtherActor);

	if (Knight) {
		Knight->DamageCharacter(DamagePoint);
		FVector LocationCharacter = Knight->GetActorLocation();
		FVector LocationLaunch    = LaunchPoint->GetComponentLocation();
		FVector LaunchDirect      = (LocationCharacter - LocationLaunch);
		LaunchDirect.Normalize();

		FVector LaunchImpulse     = LaunchForce * LaunchDirect;
		Knight->LaunchCharacter(LaunchImpulse, false, false);
	}
}
