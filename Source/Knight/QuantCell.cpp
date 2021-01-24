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

	CalculRule();
}

void UQuantCell::CalculRule()
{

	class UTileRule* NewRule = NewObject<UTileRule>(this);

	// Перебрать возможные тайлы и объединить все правила тайлов в одно правило.
	if (IsSetupTile() && InitRules.Contains(Tile))
	{
		if(InitRules.Contains(Tile))
			NewRule->Merge(InitRules[Tile]);
		else
		{
			UE_LOG(LogTemp, Error, TEXT("UQuantCell::CalculRule: Tile is unknowed!!!"));
		}
	}
	else if (Tiles.Num() > 0)
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

void UQuantCell::CalculTiles(TArray<UTileRule*> NeighborRules)
{
	if (!IsSetupTile())
	{

		//Достаем из правил соседских ячеек списки тайлов и проверяем по ним текущие тайлы, отмечая те что надо удалить.
		TSet<int> RemoveTiles;

		for (int32 Index = 0; Index != NeighborRules.Num(); ++Index)
		{
			int Dir = Dirs->Invert(Index);
			TSet <int> NeighborTiles = NeighborRules[Index]->GetTilesByDir(Dir);

			if(NeighborTiles.Num() > 0)
				for(auto& AvalibleTile : Tiles)
				{
					if (!NeighborTiles.Contains(AvalibleTile))
						RemoveTiles.Add(AvalibleTile);
				}
		}

		for (auto& RemoveTile : RemoveTiles)
			Tiles.Remove(RemoveTile);

		TArray<int> AllaivableTiles = Tiles.Array();

		if (AllaivableTiles.Num() == 1)
			Tile = AllaivableTiles[0];
	}

	CalculRule();
}

bool UQuantCell::IsSetupTile()
{
	return (Tile != -1);
}

int UQuantCell::SetupRandTile()
{
	TArray<int> AllaivableTiles = Tiles.Array();

	if (!IsSetupTile())
	{
		if (AllaivableTiles.Num() > 0)
		{
			int tileIndex = FMath::RandHelper(AllaivableTiles.Num());
			Tile = AllaivableTiles[tileIndex];
		}
		else
			UE_LOG(LogTemp, Error, TEXT("UQuantCell::SetupRandTile: Tiles.Num() is Zero!!!"));
	}

	CalculRule();

	return Tile;
}

int UQuantCell::GetTile()
{
	return Tile;
}

int UQuantCell::GetEtrop()
{
	if (!IsSetupTile() && Tiles.Num() > 0)
		return Tiles.Num() - 1;
	else
		return 0;
}

void UQuantCell::SetTile(int NewTile)
{
	Tile = NewTile;
}

class UTileRule* UQuantCell::GetRule()
{
	return Rule;
}
