// Fill out your copyright notice in the Description page of Project Settings.


#include "GenerationTileMapComponent.h"

using TArrayInt3D = TArray < TArray< TArray<int> > >;

UGenerationTileMapComponent::UGenerationTileMapComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	return;
}

void UGenerationTileMapComponent::Generation()
{	
	HashTiles = NewObject<UHashedTileSet>();
	HashMap   = NewObject<UGeneretionHashMap>();

	TArray<TArrayInt3D> HashedPatterns;
	for (auto& Pattern : TilePatterns) {
		if (Pattern != nullptr)
		{
			HashTiles->AddPattern(Pattern);
			HashedPatterns.Add( HashTiles->HashPattern(Pattern) );
		}
	}

	// UE_LOG(LogTemp, Log, TEXT("Tile number: %d"), HashTiles->GetMaxIndex());
	int32 MapWidth;
	int32 MapHeight;
	int32 NumLayers;

	GetMapSize(MapWidth,  MapHeight, NumLayers);

	MakeTileMapEditable();
	TArrayInt3D Map = HashMap->Generation(MapWidth, MapHeight, HashedPatterns);
	// auto Map = HashedPattern;

	for (int l = 0; l < Map.Num(); l++) {
		auto Layer = Map[l];

		for (int x = 0; x < Layer.Num(); x++) {
			auto Colmn = Layer[x];

			for (int y = 0; y < Colmn.Num(); y++) {

				// UE_LOG(LogTemp, Log, TEXT("x: %d, y: %d, cell: %d"), x, y, Layer[x][y]);

				FPaperTileInfo Tile = HashTiles->GetTile(Layer[x][y]);
				SetTile(x, y, l, Tile);

			}
		}
	}

	RebuildCollision();
}