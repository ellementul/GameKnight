// Copyright Epic Games, Inc. All Rights Reserved.

#include "KnightGameMode.h"
#include "KnightCharacter.h"

AKnightGameMode::AKnightGameMode()
{
	// Set default pawn class to our character
	DefaultPawnClass = AKnightCharacter::StaticClass();	
}

void AKnightGameMode::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();

	APawn* PlayerPawn = World->GetFirstPlayerController()->GetPawn();

	PlayerPawn->OnDestroyed.AddDynamic(this, &AKnightGameMode::ReSpawnCharacter);
}

void AKnightGameMode::ReSpawnCharacter(AActor* DestroyedActor)
{
	UWorld* World = GetWorld();

	APlayerController* PC = World->GetFirstPlayerController();

	RestartPlayer(PC);

	APawn* PlayerPawn = PC->GetPawn();

	PlayerPawn->OnDestroyed.AddDynamic(this, &AKnightGameMode::ReSpawnCharacter);
}

AActor* AKnightGameMode::FindPlayerStart_Implementation(AController* Player, const FString& IncomingName)
{
	UWorld* World = GetWorld();

	UKnightGameInstance* GI = Cast<UKnightGameInstance>(World->GetGameInstance());

	if (GI)
	{
		if (!GI->CurrentStartPlayerTag.IsEmpty())
		{
			return Super::FindPlayerStart_Implementation(Player, GI->CurrentStartPlayerTag);
		}
	}

	return Super::FindPlayerStart_Implementation(Player, IncomingName);
}

