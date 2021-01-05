// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TileDirects.h"
#include "TileRule.generated.h"

/*
* ��� ��������� ���������� ������� ��� ��������� �������� ������
* ������ ������ ������� ������ �� �� ������ �� ������ �����������
* ��� ���������� ����� ������ �� ������ � �������������.
* ���� ������� ���������� � ���������� ������ �� �����������
* ������ ������ ����������� �����������
* ����� ���� ���������� � ������ ��������
*
*/

UCLASS()
class KNIGHT_API UTileRule : public UObject
{
	GENERATED_BODY()

public:
	UTileRule(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer);

	void AddTileByDir(int Tile, int Dir);

	TSet<int> GetTilesByDir(int Dir);

	void Merge(UTileRule* OtherRule);

private:
	UTileDirects* Dirs;
	TArray< TSet<int> > Tiles;
	
};
