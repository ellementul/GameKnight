// Fill out your copyright notice in the Description page of Project Settings.


#include "QuantTileMap.h"
/* ����������� ����� ������ �������� ��������� �����������:
1. ���������� ������ �� ����������:
	��� ��������, 
	����� ����� � ����,
	�������� ����� ���� ����� ����.
2. ��� ����� ������ ���� ����� ������
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
