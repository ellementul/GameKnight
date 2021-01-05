// Fill out your copyright notice in the Description page of Project Settings.


#include "TileRule.h"

UTileRule::UTileRule(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	for (auto& Dir : Dirs->GetDirs()) {
		TSet<int> TileList;
		Tiles.Add(TileList);
	}
}

void UTileRule::AddTileByDir(int Tile, int Dir)
{
	if (Tiles.IsValidIndex(Dir))
		Tiles[Dir].Add(Tile);
	else
		UE_LOG(LogTemp, Error, TEXT("FTileRule::UTileRule::AddTileByDir: Dir[%d] is wrong!"), Dir);
}

TSet<int> UTileRule::GetTilesByDir(int Dir)
{
	if (Tiles.IsValidIndex(Dir)) {
		return Tiles[Dir];
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("UTileRule::GetTilesByDir: Dir[%d] is wrong!"), Dir);
		return Tiles[0];
	}
}

void UTileRule::Merge(UTileRule* OtherRule)
{
	for (int Dir = 0; Dir != Tiles.Num(); ++Dir)
	{
		for (auto& Tile : OtherRule->GetTilesByDir(Dir)) {
			AddTileByDir(Tile, Dir);
		}
	}
}
