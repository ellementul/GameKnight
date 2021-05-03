// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseBullet.h"

void ABaseBullet::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);
}

void ABaseBullet::NotifyActorBeginOverlap(AActor * OtherActor)
{
}
