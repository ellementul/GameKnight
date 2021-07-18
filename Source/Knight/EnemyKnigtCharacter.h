// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEnemyCharacter.h"
#include "Components/SphereComponent.h"
#include "EnemyKnigtCharacter.generated.h"

/**
 * 
 */
UCLASS()
class KNIGHT_API AEnemyKnigtCharacter : public ABaseEnemyCharacter
{
	GENERATED_BODY()

	AEnemyKnigtCharacter();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Hit, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* CheckHitEnemyCollision;

public:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Hit)
	TSubclassOf<AActor> EnemyClass;

	UFUNCTION(BlueprintCallable, Category = Hit)
	bool CheckHitEnemy();
	
};
