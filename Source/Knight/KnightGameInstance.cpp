// Fill out your copyright notice in the Description page of Project Settings.


#include "KnightGameInstance.h"

void UKnightGameInstance::SetStartPlayerTag(FString StartPlayerTag)
{
	if (!StartPlayerTag.IsEmpty())
	{
		CurrentStartPlayerTag = StartPlayerTag;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AKnightGameInstance::SetStartPlayerTag: Tag is empty!"));
	}
}
