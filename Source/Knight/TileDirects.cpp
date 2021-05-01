// Fill out your copyright notice in the Description page of Project Settings.


#include "TileDirects.h"

UTileDirects::UTileDirects(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Dirs.Add(0, FIntPoint(1, 0)); //Направо
	Dirs.Add(1, FIntPoint(1, -1)); //Направо-вверх
	Dirs.Add(2, FIntPoint(0, -1)); //Вверх
	Dirs.Add(3, FIntPoint(-1, -1)); //Налево-вверх
	Dirs.Add(4, FIntPoint(-1, 0)); //Налево
	Dirs.Add(5, FIntPoint(-1, 1)); //Налево-вниз
	Dirs.Add(6, FIntPoint(0, 1)); //Вниз
	Dirs.Add(7, FIntPoint(1, 1)); //Направо-вниз

	return;
}

const TArray<int> UTileDirects::GetDirs()
{
	TArray<int>  IntDirs;
	Dirs.GenerateKeyArray(IntDirs);
	return IntDirs;
}

const TArray<int> UTileDirects::GetDownToUp()
{
	TArray<int>  IntDirs;
	
	IntDirs.Add(6); //Вниз
	IntDirs.Add(7); //Направо-вниз
	IntDirs.Add(5); //Налево-вниз
	IntDirs.Add(4); //Налево
	IntDirs.Add(0); //Направо
	IntDirs.Add(1); //Направо-вверх
	IntDirs.Add(3); //Налево-вверхц
	IntDirs.Add(2); //Вверх
	
	return IntDirs;
}

int UTileDirects::GetDirByCoords(FIntPoint Coords)
{
	const int* KeyPtr = Dirs.FindKey(Coords);
	if (KeyPtr == nullptr) 
	{
		UE_LOG(LogTemp, Error, TEXT("UTileDirects::GetDirByCoords: Coords[%d,%d] is wrong!"), Coords.X, Coords.Y);
		return 0;
	}

	return *KeyPtr;
}

FIntPoint UTileDirects::GetCoords(int Dir)
{
	if (!Dirs.Contains(Dir))
	{
		UE_LOG(LogTemp, Error, TEXT("UTileDirects::GetCoords: Dirs[%d] is wrong!"), Dir);
		return Dirs[0];
	}

	return Dirs[Dir];
}

int UTileDirects::Invert(int Dir)
{
	FIntPoint Coords = GetCoords(Dir);
	return GetDirByCoords( Invert(Coords ));
}

bool UTileDirects::IsValid(int Dir)
{
	return Dirs.Contains(Dir);
}

FIntPoint UTileDirects::Invert(FIntPoint Coords)
{
	return Coords * FIntPoint(-1, -1);
}


