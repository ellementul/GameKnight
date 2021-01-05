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
	1. ������� ����� ��������� ����� � ���������� ������� ������ �������� �� ������� � �������������� ���������� ��� ��� ��������� ������
	2. ���������� ��������� ���������� ��������� ����� �������, �������� ���������� ���� ����� �� �������, ����� ���������� ��������� ������ ��� � ������ ����.
	3. ��������� ��������� ������ ������ ����� �� �����.
	4. ��������� ����� ���������� ���� �������.
 */
UCLASS()
class KNIGHT_API UGeneretionHashMap : public UObject
{
	GENERATED_UCLASS_BODY()

public:
	UGeneretionHashMap();

	TArrayInt3D Generation(int cols, int rows, TArray <TArrayInt3D> Patterns);
	

protected:
	TMap< int, struct FTileRule >   InitRules;
	TArray< TArray<UQuantCell* > >  Map;

	void CreateMap(int cols, int rows);

	bool AddPattern(TArrayInt3D Pattern);
	struct FTileRule AddRule(struct FTileRule Rule, TArray< TArray<int> > Layer, FIntPoint Coord);

	bool GetTile(TArray< TArray<int> > layer, FIntPoint coord, int& tile);

	struct FTileDirects Dirs;
};



