// Fill out your copyright notice in the Description page of Project Settings.


#include "GenerationTileMapComponent.h"

using TArrayInt3D = TArray < TArray< TArray<int> > >;

UGenerationTileMapComponent::UGenerationTileMapComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	HashTiles = CreateDefaultSubobject<UHashedTileSet>(TEXT("HashTiles"));
	GenMap    = CreateDefaultSubobject<UGeneretionHashMap>(TEXT("GenMap"));

	return;
}

void UGenerationTileMapComponent::Build()
{
	DefaultHashedMap = HashTiles->HashPattern(BeginTileMap);

	for (auto& Pattern : TilePatterns) {
		if (Pattern != nullptr)
		{
			HashedPatterns.Add(HashTiles->HashPattern(Pattern));
		}
	}

	// UE_LOG(LogTemp, Log, TEXT("Tile number: %d"), HashTiles->GetMaxIndex());
}

void UGenerationTileMapComponent::Generation()
{
	MakeTileMapEditable();

	TArrayInt3D HashedMap = GenMap->Generation(DefaultHashedMap, HashedPatterns);

	for (int l = 0; l < HashedMap.Num(); l++) {
		auto Layer = HashedMap[l];

		for (int x = 0; x < Layer.Num(); x++) {
			auto Colmn = Layer[x];

			for (int y = 0; y < Colmn.Num(); y++) {

				int TileIndex = Layer[x][y];
				FPaperTileInfo Tile = ErrorTile;

				if (TileIndex > -1)
					 Tile = HashTiles->GetTile(TileIndex);
				else
					UE_LOG(LogTemp, Error, TEXT("x: %d, y: %d, cell: %d"), x, y, Layer[x][y]);

				SetTile(x, y, l, Tile);
			}
		}
	}

	RebuildCollision();
}

TArray<FActorSpawning> UGenerationTileMapComponent::GetBindActors()
{
	TArray<FActorSpawning> Actors;

	for (int l = 0; l < TileMap->TileLayers.Num(); l++) {

		for (int x = 0; x < TileMap->MapWidth; x++) {

			for (int y = 0; y < TileMap->MapHeight; y++) 
			{
				FPaperTileInfo Tile = TileMap->TileLayers[l]->GetCell(x, y);
				UClass* ClassActor = GetBindActor(Tile);

				if (ClassActor)
				{
					FActorSpawning ActorSpawning = FActorSpawning();
					ActorSpawning.ClassActor = ClassActor;
					ActorSpawning.Location   = TileMap->GetTilePositionInLocalSpace(x, y, l);
					ActorSpawning.Location.X += TileMap->TileWidth / 2;
					ActorSpawning.Location.Z -= TileMap->TileHeight / 2;

					Actors.Add(ActorSpawning);

					SetTile(x, y, l, FPaperTileInfo());
				}
			}
		}
	}

	return Actors;
}

class TSubclassOf<APaperSpriteActor>  UGenerationTileMapComponent::GetBindActor(FPaperTileInfo Tile)
{
	for (auto& Trigger : Triggers)
	{
		if (Trigger.Tile == Tile)
		{
			return Trigger.Actor;	
		}
	}

	return nullptr;
}

void UGenerationTileMapComponent::Clear()
{
	for (int l = 0; l < TileMap->TileLayers.Num(); l++) {

		for (int x = 0; x < TileMap->MapWidth; x++) {

			for (int y = 0; y < TileMap->MapHeight; y++) {

				SetTile(x, y, l, FPaperTileInfo());
			}
		}
	}
}
