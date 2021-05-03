// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "BaseBullet.h"
#include "BaseEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class KNIGHT_API ABaseEnemyCharacter : public ABaseCharacter
{
	GENERATED_BODY()

	ABaseEnemyCharacter();
	
protected:

	virtual void UpdateAnimState() override;
	virtual bool IsIdle() override;

	virtual bool Damaged(int Damage) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	FAnimState WalkState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	FAnimState JumpState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Damaged)
	TSubclassOf<ABaseBullet> BulletClass;

public:

	virtual void Attack() override;
};
