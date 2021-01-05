#pragma once
#include "CoreMinimal.h"
#include "TileDirects.h"
#include "TileRule.h"

#include "QuantCell.generated.h"

/**
 * ласс €чейки на на карте
 * —одержит правило дл€ соседних €чеек и список возможных тайлов дл€ этой €чейки
 »меет функцию установки начального набора тайлов и правил дл€ них.
 * »меет функцию перерасчета правила дл€ этой €чейки.
 *		Ёта фукнци€ принимает:
 *			четыре списка возможных тайлов из соседних €чеек по четырем напралени€м к этому тайлу
 *          общий сборник правил дл€ каждого тайла
 »меет функцию проверки, определен ли уже тайл дл€ этой €чейки.
 »меет функцию расчета котора€ уточн€ет список возможных тайлов в этой €чейке, требует сет четырех правил из соседних €чеек по одному на каждое нарпавление
 »меет функцию установки рандомного тайла из возможных.

 *
 */

UCLASS()
class KNIGHT_API UQuantCell : public UObject
{
	GENERATED_UCLASS_BODY()

public:
	void SetupRules(TMap< int, UTileRule* > Rules);

	void CalculRule();

	int CalculTiles(TArray< UTileRule* > NeighborRules);

	
	bool IsSetupTile();

	int SetupRandTile();

	int GetTile();
	const UTileRule* GetRule();

private:
	TMap< int, UTileRule* > InitRules;
	class UTileRule* Rule;
	TSet<int> Tiles;

	int Tile;

	class UTileDirects* Dirs;
};
