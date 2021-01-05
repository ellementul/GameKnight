#pragma once
#include "CoreMinimal.h"
#include "TileDirects.h"
#include "TileRule.h"

#include "QuantCell.generated.h"

/**
 *����� ������ �� �� �����
 * �������� ������� ��� �������� ����� � ������ ��������� ������ ��� ���� ������
 ����� ������� ��������� ���������� ������ ������ � ������ ��� ���.
 * ����� ������� ����������� ������� ��� ���� ������.
 *		��� ������� ���������:
 *			������ ������ ��������� ������ �� �������� ����� �� ������� ����������� � ����� �����
 *          ����� ������� ������ ��� ������� �����
 ����� ������� ��������, ��������� �� ��� ���� ��� ���� ������.
 ����� ������� ������� ������� �������� ������ ��������� ������ � ���� ������, ������� ��� ������� ������ �� �������� ����� �� ������ �� ������ �����������
 ����� ������� ��������� ���������� ����� �� ���������.

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
