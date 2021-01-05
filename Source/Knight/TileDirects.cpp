// Fill out your copyright notice in the Description page of Project Settings.


#include "TileDirects.h"

UTileDirects::UTileDirects(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	Dirs.Add(0, FIntPoint(1, 0));
	Dirs.Add(1, FIntPoint(0, 1));
	Dirs.Add(2, FIntPoint(-1, 0));
	Dirs.Add(3, FIntPoint(0, -1));
}

const TArray<int> UTileDirects::GetDirs()
{
	TArray<int>  IntDirs;
	Dirs.GenerateKeyArray(IntDirs);
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
	int InvertDir = 0;
	switch (Dir)
	{
	case 0:  InvertDir = 2;
		break;
	case 1:  InvertDir = 3;
		break;
	case 2:  InvertDir = 0;
		break;
	case 3:  InvertDir = 1;
		break;
	default:
		UE_LOG(LogTemp, Error, TEXT(" UTileDirects::Invert: Dir[%d] is wrong!"), Dir);
	}

	return InvertDir;
}

FIntPoint UTileDirects::Invert(FIntPoint Coords)
{
	return GetCoords( Invert(GetDirByCoords(Coords)) );
}


