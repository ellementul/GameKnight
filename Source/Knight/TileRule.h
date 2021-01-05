// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TileDirects.h"
#include "TileRule.generated.h"

/*
* Это структура определяет правило для возможных соседних тайлов
* Хранит четыре массива тайлов по по одному на каждое направление
* Все экземпляры имеют ссылку на массив с направлениями.
* Имет фукнцию добавления в конкретный массив по направлению
* Отдает массив конкретного направления
* Может быть объединено с другим правилом
*
*/

UCLASS()
class KNIGHT_API UTileRule : public UObject
{
	GENERATED_UCLASS_BODY()

public:
	void AddTileByDir(int Tile, int Dir);

	TSet<int> GetTilesByDir(int Dir);

	void Merge(UTileRule* OtherRule);

private:
	class UTileDirects* Dirs;
	TArray< TSet<int> > Tiles;
	
};
