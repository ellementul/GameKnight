// Fill out your copyright notice in the Description page of Project Settings.


#include "QuantTileMap.h"
/* Хэширование тайла должно отвечать следующим требованиям:
1. Полагаться только на информацию:
	Имя тайлсета, 
	Номер тайла в сете,
	Повороты тайла если такие есть.
2. Хэш тайла должен быть целым числом
*/

UQuantTileMap::UQuantTileMap(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	
	HashTileMap = CreateDefaultSubobject<UHashedTileSet>(TEXT("HashTileMap"));

	return;
}

TArray<TArray<TArray<int>>> UQuantTileMap::GetHashedMap()
{
	return HashTileMap->HashPattern(this);
}

int UQuantTileMap::GetIndexForTile(FPaperTileInfo Tile)
{
	return HashTileMap->GetIndex(Tile);
}

int UQuantTileMap::GetMaxTileIndex()
{
	return HashTileMap->GetMaxIndex();
}

FPaperTileInfo UQuantTileMap::GetTileForIndex(int TileIndex)
{
	return HashTileMap->GetTile(TileIndex);
}
