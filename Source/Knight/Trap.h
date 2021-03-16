// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperSpriteActor.h"
#include "Components/SceneComponent.h"
#include "KnightCharacter.h"
#include "Trap.generated.h"

class AKnightCharacter;
class USceneComponent;

/**
 * 
 */
UCLASS()
class KNIGHT_API ATrap : public APaperSpriteActor
{
	GENERATED_BODY()

	ATrap();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* LaunchPoint;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HealthAndDamage)
	int DamagePoint = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HealthAndDamage)
	float LaunchForce = 1000;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor);
	
};
