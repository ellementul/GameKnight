// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperSpriteActor.h"
#include "KnightCharacter.h"
#include "Trap.generated.h"

class AKnightCharacter;

/**
 * 
 */
UCLASS()
class KNIGHT_API ATrap : public APaperSpriteActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HealthAndDamage)
	int DamagePoint = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HealthAndDamage)
	float LaunchForce = 1000;

	virtual void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit);
	
};
