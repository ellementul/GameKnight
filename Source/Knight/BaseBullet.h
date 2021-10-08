// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbookActor.h"
#include "KnightCharacter.h"
#include "BaseEnemyCharacter.h"
#include "LaunchAimInterface.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "BaseBullet.generated.h"

/**
 * 
 */
UCLASS()
class KNIGHT_API ABaseBullet : public APaperFlipbookActor, public ILaunchAimInterface
{
	GENERATED_BODY()

	ABaseBullet();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Sound, meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* Movement;

	float OneTileSpeed = 128;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	FTimerHandle BeginTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Damage)
	int DamagePoint = 1;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor);

public:

	virtual void LaunchAim(FVector Target) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bullet)
	float IsGravity = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bullet)
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bullet)
	float LaunchForce = 1000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bullet)
	float LifeTime = 1.0;
	
	void DestroyBullet();
};