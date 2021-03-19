#pragma once

#include "CoreMinimal.h"
#include "PaperSpriteActor.h"
#include "PaperTileSet.h"
#include "PaperTileMap.h"
#include "PaperTileMapComponent.h"
#include "HashedTileSet.h"
#include "GeneretionHashMap.h"

#include "GenerationTileMapComponent.generated.h"

class APaperSpriteActor;
class UPaperTileMap;
class UHashedTileSet;
class UGeneretionHashMap;

USTRUCT(BlueprintType)
struct FActorBindTile {

	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FPaperTileInfo ActorTile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class TSubclassOf<APaperSpriteActor> Actor;

};

/**
 * 
 */
UCLASS(hideCategories = Object, ClassGroup = Paper2D, EarlyAccessPreview, meta = (BlueprintSpawnableComponent))
class KNIGHT_API UGenerationTileMapComponent : public UPaperTileMapComponent
{
	GENERATED_UCLASS_BODY()

public:

	UGenerationTileMapComponent();

	UPROPERTY(Category = Tiles, EditAnywhere, BlueprintReadWrite)
		TArray<UPaperTileMap*> TilePatterns;

	UPROPERTY(Category = Tiles, EditAnywhere, BlueprintReadWrite)
		FPaperTileInfo ErrorTile;

	UPROPERTY(Category = TriggersAndCharacters, EditAnywhere, BlueprintReadWrite)
		TArray<FActorBindTile> Triggers;

	UFUNCTION(BlueprintCallable, Category = "Sprite")
		void Generation();

	UFUNCTION(BlueprintCallable, Category = "Sprite")
		void Clear();

private:
	class UHashedTileSet* HashTiles;

	class UGeneretionHashMap* GenMap;
};
