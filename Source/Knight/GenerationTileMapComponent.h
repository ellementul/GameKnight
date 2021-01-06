#pragma once

#include "CoreMinimal.h"
#include "PaperTileSet.h"
#include "PaperTileMap.h"
#include "PaperTileMapComponent.h"
#include "HashedTileSet.h"
#include "GeneretionHashMap.h"

#include "GenerationTileMapComponent.generated.h"

class UPaperTileMap;
class UHashedTileSet;
class UGeneretionHashMap;

/**
 * 
 */
UCLASS(hideCategories = Object, ClassGroup = Paper2D, EarlyAccessPreview, meta = (BlueprintSpawnableComponent))
class KNIGHT_API UGenerationTileMapComponent : public UPaperTileMapComponent
{
	GENERATED_UCLASS_BODY()

public:

	UGenerationTileMapComponent();

	UPROPERTY(Category = Setup, EditAnywhere, BlueprintReadWrite)
		TArray<UPaperTileMap*> TilePatterns;

	UPROPERTY(Category = Setup, EditAnywhere, BlueprintReadWrite)
		FPaperTileInfo ErrorTile;

	UFUNCTION(BlueprintCallable, Category = "Sprite")
		void Generation();

private:
	class UHashedTileSet* HashTiles;

	class UGeneretionHashMap* HashMap;
};
