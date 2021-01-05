// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TileDirects.generated.h"

/*
* ���n ����� ���������� ����������� ��� �����
* �����������:
* 0 - ������������� ������� X
* 1 - ������������� ������� Y
* 2 - ������������� ������� X
* 3 - ������������� ������� Y
*/
UCLASS()
class KNIGHT_API UTileDirects : public UObject
{
	GENERATED_BODY()

public:

	UTileDirects(const FObjectInitializer& ObjectInitializer);

	const TArray<int> GetDirs();

	int GetDirByCoords(FIntPoint Coords);

	FIntPoint GetCoords(int Dir);

	FIntPoint Invert(FIntPoint Coords);

	int       Invert(int Dir);

private:
	TMap<int, FIntPoint> Dirs;
	
};
