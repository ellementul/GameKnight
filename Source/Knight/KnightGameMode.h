// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "KnightGameMode.generated.h"

/**
 * The GameMode defines the game being played. It governs the game rules, scoring, what actors
 * are allowed to exist in this game type, and who may enter the game.
 *
 * This game mode just sets the default pawn to be the MyCharacter asset, which is a subclass of KnightCharacter
 */
UCLASS()
class AKnightGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	AKnightGameMode();

	virtual AActor* FindPlayerStart_Implementation(AController* Player, const FString& IncomingName) override;

	UFUNCTION()
	void SetStartPlayerTag(FString StartPlayerTag);

protected:

	virtual void BeginPlay() override;

	UFUNCTION()
	void ReSpawnCharacter(AActor* DestroyedActor);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerStart)
	FString CurrentStartPlayerTag;
};
