// Fill out your copyright notice in the Description page of Project Settings.


#include "KnightPlayerStart.h"

AKnightPlayerStart::AKnightPlayerStart(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SpawnLabel = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("SpawnLabel"));
	SpawnLabel->SetCollisionProfileName("OverlapAllDynamic", true);
	SpawnLabel->SetupAttachment(RootComponent);
}

void AKnightPlayerStart::NotifyActorBeginOverlap(AActor * OtherActor)
{
	AKnightCharacter* Knight = Cast<AKnightCharacter>(OtherActor);

	if (Knight) {
		UWorld* World = GetWorld();

		AKnightGameMode* GameMode = Cast<AKnightGameMode>( World->GetAuthGameMode() );

		if (GameMode)
		{
			GameMode->SetStartPlayerTag(PlayerStartTag.ToString());
		}
	}
}
