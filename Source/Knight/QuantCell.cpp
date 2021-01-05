// Fill out your copyright notice in the Description page of Project Settings.


#include "QuantCell.h"


UQuantCell::UQuantCell(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	/*struct FConstructorStatics
	{
		struct FTileDirects Dirs;
	}

	static FConstructorStatics ConstructorStatics;

	Dirs = ConstructorStatics.Dirs;
	*/

	Tile = -1;

	return;
}

void UQuantCell::SetupRules(TMap<int, UTileRule*> Rules)
{
	InitRules = Rules;

	TArray<int>  InitTiles;
	InitRules.GenerateKeyArray(InitTiles);

	Tiles.Empty();
	for(auto& InitTile : InitTiles)
		Tiles.Add(InitTile);
}

void UQuantCell::CalculRule()
{

	class UTileRule* NewRule = NewObject<UTileRule>(this);

	// Перебрать возможные тайлы и объединить все правила тайлов в одно правило.
	if (Tiles.Num() > 0)
		for (auto& AvallibleTile : Tiles)
			NewRule->Merge(InitRules[AvallibleTile]);

	else
	{
		UE_LOG(LogTemp, Error, TEXT("UQuantCell::CalculRule: Tiles.Num() is Zero!!!"));

		for (auto& InitRule : InitRules)
			NewRule->Merge(InitRule.Value);
	}

	Rule = NewRule;
}

int UQuantCell::CalculTiles(TArray<UTileRule*> NeighborRules)
{
	if (!IsSetupTile())
	{
		TSet <int> NeighborTiles;

		////Достаем из правил соседских ячеек списки тайлов и объединям их.
		//for (int32 Index = 0; Index != NeighborRules.Num(); ++Index)
		//{
		//	int Dir = Dirs->Invert(Index);
		//	TSet <int> NeighborTiles = NeighborRules->GetTilesByDir(Dir);

		//	//Отбрасываем те возможные тайлы которых нет в этом списке тайлов.
		//}

		//Tiles = NeighborTiles;

		TArray<int> AllaivableTiles = Tiles.Array();

		if (AllaivableTiles.Num() == 1)
			Tile = AllaivableTiles[0];
	}

	return Tiles.Num();
}

bool UQuantCell::IsSetupTile()
{
	return (Tile != -1);
}

int UQuantCell::SetupRandTile()
{
	TArray<int> AllaivableTiles = Tiles.Array();

	if (AllaivableTiles.Num() > 0)
	{
		int tileIndex = FMath::RandHelper(AllaivableTiles.Num());
		Tile = AllaivableTiles[tileIndex];
	}
	else
		UE_LOG(LogTemp, Error, TEXT("UQuantCell::SetupRandTile: Tiles.Num() is Zero!!!"));

	return Tile;
}

int UQuantCell::GetTile()
{
	return Tile;
}
const UTileRule* UQuantCell::GetRule()
{
	return Rule;
}
