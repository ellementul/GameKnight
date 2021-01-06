#pragma once

#include "CoreMinimal.h"

#include "HashedTileSet.h"

#include "TileDirects.h"
#include "TileRule.h"
#include "QuantCell.h"

#include "GeneretionHashMap.generated.h"

using TArrayInt3D = TArray < TArray< TArray<int> > >;

class UQuantCell;

/**
	Этот класс генерирует карту по заданным параметрам.
	Для генерации передаются размеры карты и паттерны для обучения генератора
	С помощью исследования патернов выясняются правила стыковки соседних тайлов
	Далее создается карта где каждая ячейка содержит свой набор возможных тайлов
	Паттерны длется по уровням по размеру от крупных к мелким.
	Берутся паттерны первого уровня и ими заполнятеся карта
			с расчетом чтобы между ними было расстояние не меньше чем размер паттерна следующего уровня
		"Схлапываем" количество возможностей для ячеек которые не были заполнены паттернами.
	Затем повторяем это для остальных уровней паттернов, исключая условие расстояния между патернами, 
			теперь его может не быть если паттерн хорошо помещается между двумя другими
	Последний уровен патернов должен быть не меньше чем 3х3. 
	После того как на карте остались промежутке не больше чем 2 ечейки в ширину, мы заполняем осташиеся ячейки возможными тайлами, 
			используя рандомный выбор если возможностей все еще несколько.
	Если появилась ячейка у которой не осталось не одного возможного тайла, то кидаем прудпреждение и назначаем индекс тайла в -1

	TODO:
	0. Создаем карту квантовых ячеек и определяем какждую ячейку рандомно по порядку
	1. Создаем карту квантовых ячеек и определяем какждую ячейку рандомно по порядку с преварительным перерасчет для нее возможных тайлов
	2. Определяем некоторое количество рандомных ячеек заренее, проводим перерасчет всех ячеек по порядку, потом определяем остальные ячейки как в первом шаге.
	3. Заполняем патернами одного уровня карту на пробу.
	4. Заполняем карту паттернами всех уровней.
 */
UCLASS()
class KNIGHT_API UGeneretionHashMap : public UObject
{
	GENERATED_UCLASS_BODY()

public:
	TArrayInt3D Generation(int cols, int rows, TArray <TArrayInt3D> Patterns);
	

protected:
	TMap< int, UTileRule* >   InitRules;
	TArray< TArray<UQuantCell* > >  Map;

	void CreateMap(int cols, int rows);

	bool AddPattern(TArrayInt3D Pattern);
	class UTileRule* AddRule(TArray< TArray<int> > Layer, FIntPoint Coord);

	TArray<UTileRule*> GetNeighborRules(FIntPoint Coord);

	bool GetTile(TArray< TArray<int> > Layer, FIntPoint Coord, int& Tile);
	class UQuantCell* GetCell(FIntPoint Coord);

	class UTileDirects* Dirs;
};



