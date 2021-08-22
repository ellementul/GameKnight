// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "LaunchAimInterface.h"
#include "BaseEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class KNIGHT_API ABaseEnemyCharacter : public ABaseCharacter
{
	GENERATED_BODY()
	
protected:

	virtual void UpdateAnimState() override;
	virtual bool IsIdle() override;

	virtual bool Damaged(int Damage) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	FAnimState WalkState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	FAnimState JumpState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	FAnimState SpeakState;

public:

	virtual void Attack(FVector Target) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character)
	float SeeEnemyDistance = 150;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	bool IsSpeak = false;
};
