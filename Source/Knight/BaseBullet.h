// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbookActor.h"
#include "BaseBullet.generated.h"

/**
 * 
 */
UCLASS()
class KNIGHT_API ABaseBullet : public APaperFlipbookActor
{
	GENERATED_BODY()

protected:

	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Damage)
	int DamagePoint = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Moving)
	FVector Speed;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor);
};
