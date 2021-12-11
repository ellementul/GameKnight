// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "KnightGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class KNIGHT_API UKnightGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void SetStartPlayerTag(FString StartPlayerTag);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerStart)
	FString CurrentStartPlayerTag;
	
};
