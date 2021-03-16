// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerStart.h"
#include "PaperSpriteComponent.h"
#include "KnightCharacter.h"
#include "KnightGameMode.h"
#include "KnightPlayerStart.generated.h"

class AKnightCharacter;
class AKnightGameMode;

/**
 * 
 */
UCLASS(Blueprintable, ClassGroup = Common, hidecategories = Collision)
class KNIGHT_API AKnightPlayerStart : public APlayerStart
{
	GENERATED_BODY()

	AKnightPlayerStart(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UPaperSpriteComponent* SpawnLabel;

protected:
	virtual void NotifyActorBeginOverlap(AActor* OtherActor);

};
