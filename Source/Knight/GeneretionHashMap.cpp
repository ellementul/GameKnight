// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneretionHashMap.h"

UGeneretionHashMap::UGeneretionHashMap(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

	Dirs = this->CreateDefaultSubobject<UTileDirects>("Dirs");

	TArray<FIntPoint> ZeroEntropLevel;
	EntropLevels.Add(ZeroEntropLevel);

	return;
}

void UGeneretionHashMap::CreateMap(TArrayInt3D BeginMap)
{
	TArray< TArray<int> >  FirstLayer = BeginMap[0];

	for (int X = 0; X < FirstLayer.Num(); X++)
	{
		TArray<UQuantCell*> Colmn;

		for (int Y = 0; Y < FirstLayer[X].Num(); Y++)
		{
			UQuantCell* Cell = NewObject<UQuantCell>(this);

			if (FirstLayer[X][Y] != 0)
				Cell->SetTile(FirstLayer[X][Y]);

			Colmn.Add(Cell);
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

TArrayInt3D UGeneretionHashMap::Generation(TArrayInt3D BeginMap, TArray <TArrayInt3D> Patterns)
{
	
	CreateMap(BeginMap);

	//Добавляем паттерны и вычисляем по ним правила.
	for (auto& pattern : Patterns) {
		AddPattern(pattern);
	}

	//По количеству тайлов создаем уровни этропии
	TArray<int> Tiles;
	InitRules.GenerateKeyArray(Tiles);

	for (auto& Tile : Tiles) {
		TArray<FIntPoint> EntropLevel;
		EntropLevels.Add(EntropLevel);
	}

	//Добавляем правила в каждую ячейку.
	for (auto& Colmn : Map)
		for (auto& Cell : Colmn)
			Cell->SetupRules(InitRules);

	//Вычисляем этропию и заполняем уровени этропии
	for (int Y = Map[0].Num() - 1; Y >= 0; Y--)
		for (int X = 0; X < Map.Num(); X++)
		{
			auto Cell = Map[X][Y];
			auto NeighborRules = GetNeighborRules(FIntPoint(X, Y));

			Cell->CalculTiles(NeighborRules);

			int Etrop = Cell->GetEtrop();

			if (Cell->IsSetupTile()) {
				EntropLevels[0].Add(FIntPoint(X, Y));
				CalculNeighborTileEtrop(FIntPoint(X, Y));
			}
		}
	

	//Перебираем тайлы по уровням этропии пока все уровни не опустеют.
	CalcQuantMap();


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

void UGeneretionHashMap::CalcQuantMap() 
{
	bool IsNotEmpty = true;

	while (IsNotEmpty) {
		IsNotEmpty = false;

		//Находим первый не пустой уровень  с не нулевой этропией.
		for (int L = 1; L < EntropLevels.Num(); L++)
		{

			if (EntropLevels[L].IsValidIndex(0)) 
			{
				IsNotEmpty = true;

				//Берем с уровня первую ячейку, данные о этропии которой не устарели.

				auto Coords = EntropLevels[L][0];
				EntropLevels[L].RemoveAt(0);

				UQuantCell* Cell = GetCell(Coords);

				//Если ячейка все еще на этом уровне то берем ее.
				if (Cell->GetEtrop() == L) {
					Cell->SetupRandTile();
					CalculNeighborTileEtrop(Coords);

					break;
				}
			}
		}
	}
}

void UGeneretionHashMap::CalculNeighborTileEtrop(FIntPoint Coords)
{
	for (auto& Dir : Dirs->GetDownToUp()) {

		auto shiftCoord = Coords + Dirs->GetCoords(Dir);

		UQuantCell* Cell = GetCell(shiftCoord);

		if (Cell != nullptr) {
			auto NeighborRules = GetNeighborRules(shiftCoord);

			int OldEntrop = Cell->GetEtrop();
			Cell->CalculTiles(NeighborRules);
			int Entrop = Cell->GetEtrop();

			//Если этропия тайла изменилась, то рекурсивно проверяем всех его соседей.
			if (OldEntrop > Entrop) {
				EntropLevels[Entrop].Add(shiftCoord);
				CalculNeighborTileEtrop(shiftCoord);
			}
		}
	}
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




	


