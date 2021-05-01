// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperTileMap.h"
#include "HashedTileSet.h"
#include "QuantTileMap.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class KNIGHT_API UQuantTileMap : public UPaperTileMap
{
	GENERATED_BODY()

	UQuantTileMap(const FObjectInitializer& ObjectInitializer);

public:

	TArray < TArray< TArray<int> > > GetHashedMap();

	int GetIndexForTile(FPaperTileInfo Tile);

	int GetMaxTileIndex();

	struct FPaperTileInfo GetTileForIndex(int TileIndex);

private:
	UHashedTileSet* HashTileMap;
};
