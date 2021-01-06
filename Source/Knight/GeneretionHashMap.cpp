// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneretionHashMap.h"

UGeneretionHashMap::UGeneretionHashMap(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Dirs = this->CreateDefaultSubobject<UTileDirects>("Dirs");
	return;
}

TArrayInt3D UGeneretionHashMap::Generation(int cols, int rows, TArray <TArrayInt3D> Patterns)
{
	
	CreateMap(cols, rows);

	for (auto& pattern : Patterns) {
		AddPattern(pattern);
	}

	for (auto& Colmn : Map)
		for (auto& Cell : Colmn)
			Cell->SetupRules(InitRules);
		
	for (int X = 0; X < Map.Num(); X++)
	{
		auto Column = Map[X];

		for (int Y = 0; Y < Column.Num(); Y++)
		{
			auto Cell = Column[Y];
			auto NeighborRules = GetNeighborRules(FIntPoint(X, Y));

			Cell->CalculTiles(NeighborRules);
			Cell->SetupRandTile();
		}

	}



	TArray< TArray<int> > Layer;

	for (int X = 0; X < Map.Num(); X++)
	{
		TArray<int> Colmn;

		for (int Y = 0; Y < Map[X].Num(); Y++)
			Colmn.Add(Map[X][Y]->GetTile());

		Layer.Add(Colmn);
	}

	TArrayInt3D HMap;
	HMap.Add(Layer);

	return HMap;
}

void UGeneretionHashMap::CreateMap(int cols, int rows)
{
	for (int i = 0; i < cols; i++) {
		TArray<UQuantCell*> Colmn;

		for (int j = 0; j < rows; j++) {
			Colmn.Add(NewObject<UQuantCell>(this));
		}

		Map.Add(Colmn);
	}
}

bool UGeneretionHashMap::AddPattern(TArrayInt3D Pattern)
{
	for (int l = 0; l < Pattern.Num(); l++) {
		auto Layer = Pattern[l];

		for (int x = 0; x < Layer.Num(); x++) {
			auto Colmn = Layer[x];

			for (int y = 0; y < Colmn.Num(); y++) {

				class UTileRule* NewRule = AddRule(Layer, FIntPoint(x, y));

				int RuleIndex = Colmn[y];

				if (InitRules.Contains(RuleIndex))
				{
					class UTileRule* OldRule = InitRules[RuleIndex];
					NewRule->Merge(OldRule);
				}
				
				InitRules.Add(RuleIndex, NewRule);

			}
		}
	}

	TArray<int> tiles;
	InitRules.GenerateKeyArray(tiles);
	auto Rule = InitRules[tiles[1]];

	UE_LOG(LogTemp, Log, TEXT("Rule number %d bottom: %d"), tiles[1], Rule->GetTilesByDir(1).Num());

	return true;
}

class UTileRule* UGeneretionHashMap::AddRule(TArray< TArray<int> > Layer, FIntPoint Coord)
{
	class UTileRule* NewRule = NewObject<UTileRule>(this);

	for (auto& Dir : Dirs->GetDirs()) {

		auto shiftCoord = Coord + Dirs->GetCoords(Dir);

		int Tile;
		if (GetTile(Layer, shiftCoord, Tile))
			NewRule->AddTileByDir(Tile, Dir);
	}

	return NewRule;
}

TArray<UTileRule*> UGeneretionHashMap::GetNeighborRules(FIntPoint Coord)
{
	TArray<UTileRule*> NeighborRules;

	for (auto& Dir : Dirs->GetDirs()) {

		auto shiftCoord = Coord + Dirs->GetCoords(Dir);

		UQuantCell* Cell = GetCell(shiftCoord);

		if (Cell != nullptr)
			NeighborRules.Add(Cell->GetRule());
		else
			NeighborRules.Add(NewObject<UTileRule>(this));
	}

	return NeighborRules;
}

bool UGeneretionHashMap::GetTile(TArray<TArray<int>> Layer, FIntPoint Coord, int& Tile)
{
	int x = Coord.X;
	int y = Coord.Y;

	if (Layer.IsValidIndex(x) && Layer[x].IsValidIndex(y))
	{
		Tile = Layer[x][y];
		return true;
	}

	return false;
}

UQuantCell* UGeneretionHashMap::GetCell(FIntPoint Coord)
{
	int x = Coord.X;
	int y = Coord.Y;

	if (Map.IsValidIndex(x) && Map[x].IsValidIndex(y))
		return Map[x][y];
	else
		return nullptr;
}


	


