// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperTileSet.h"
#include "PaperTileLayer.h"
#include "PaperTileMap.h"

#include "HashedTileSet.generated.h"

/**
 * 
 */
UCLASS()
class KNIGHT_API UHashedTileSet : public UObject
{
	GENERATED_UCLASS_BODY()

public:
	UHashedTileSet();

	bool AddPattern(UPaperTileMap* TileMap);

	TArray < TArray< TArray<int> > > HashPattern(UPaperTileMap* TileMap);

	int GetIndex(FPaperTileInfo Tile);

	int GetMaxIndex();

	struct FPaperTileInfo GetTile(int TileIndex);

private:
	TArray<FPaperTileInfo> TileSet;


	int AddTile(FPaperTileInfo Tile);
};
