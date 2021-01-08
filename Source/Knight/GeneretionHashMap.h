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
	���� ����� ���������� ����� �� �������� ����������.
	��� ��������� ���������� ������� ����� � �������� ��� �������� ����������
	� ������� ������������ �������� ���������� ������� �������� �������� ������
	����� ��������� ����� ��� ������ ������ �������� ���� ����� ��������� ������
	�������� ������ �� ������� �� ������� �� ������� � ������.
	������� �������� ������� ������ � ��� ����������� �����
			� �������� ����� ����� ���� ���� ���������� �� ������ ��� ������ �������� ���������� ������
		"����������" ���������� ������������ ��� ����� ������� �� ���� ��������� ����������.
	����� ��������� ��� ��� ��������� ������� ���������, �������� ������� ���������� ����� ���������, 
			������ ��� ����� �� ���� ���� ������� ������ ���������� ����� ����� �������
	��������� ������ �������� ������ ���� �� ������ ��� 3�3. 
	����� ���� ��� �� ����� �������� ���������� �� ������ ��� 2 ������ � ������, �� ��������� ��������� ������ ���������� �������, 
			��������� ��������� ����� ���� ������������ ��� ��� ���������.
	���� ��������� ������ � ������� �� �������� �� ������ ���������� �����, �� ������ ������������� � ��������� ������ ����� � -1

	TODO:
	0. ������� ����� ��������� ����� � ���������� ������� ������ �������� �� �������
	1. ������� �����, � ��������� �� � ���������� � ��������� �������� ������, �������� �� �������.
	2. ������� ����� �� ��� ������������ ����� ������, � ��������� �� �� �������.
	3. ������� �����, ��������� �� �� ������� ������� �������� ������ ������ �������� ������ �������, � ��������� ������ ������� ���� ������ �� ������� �������.
	4. ����� ���������� ������� ����� ��������� ��� ������� �� ��������� �������.
	4.1. ��������� ������ ������� �������� �����
	4.2. ��������� ���������� ���� ������� ������� ��� ��� ������� ���� ��������.
 */
UCLASS()
class KNIGHT_API UGeneretionHashMap : public UObject
{
	GENERATED_UCLASS_BODY()

public:
	TArrayInt3D Generation(TArrayInt3D BeginMap, TArray <TArrayInt3D> Patterns);
	

protected:
	TMap< int, UTileRule* >   InitRules;
	TArray< TArray<UQuantCell* > >  Map;

	TArray<TArray<FIntPoint>> EntropLevels;

	void CreateMap(TArrayInt3D BeginMap);

	bool AddPattern(TArrayInt3D Pattern);
	class UTileRule* AddRule(TArray< TArray<int> > Layer, FIntPoint Coord);

	TArray<UTileRule*> GetNeighborRules(FIntPoint Coord);

	bool GetTile(TArray< TArray<int> > Layer, FIntPoint Coord, int& Tile);
	class UQuantCell* GetCell(FIntPoint Coord);

	void CalcQuantMap();

	void CalculNeighborTileEtrop(FIntPoint Coords);

	class UTileDirects* Dirs;
};



