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
	FPaperTileInfo Tile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class TSubclassOf<APaperSpriteActor> Actor;
};

USTRUCT(BlueprintType)
struct FActorSpawning {

	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class TSubclassOf<APaperSpriteActor> ClassActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Location;
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
		class UPaperTileMap* BeginTileMap;

	UPROPERTY(Category = Tiles, EditAnywhere, BlueprintReadWrite)
		TArray<UPaperTileMap*> TilePatterns;

	UPROPERTY(Category = Tiles, EditAnywhere, BlueprintReadWrite)
		FPaperTileInfo ErrorTile;

	UPROPERTY(Category = TriggersAndCharacters, EditAnywhere, BlueprintReadWrite)
		TArray<FActorBindTile> Triggers;

	UFUNCTION(BlueprintCallable, Category = Category = TriggersAndCharacters)
	TArray<FActorSpawning> GetBindActors();

	UFUNCTION(BlueprintCallable, Category = "TileMap")
	void Build();

	UFUNCTION(BlueprintCallable, Category = "TileMap")
	void Generation();

	UFUNCTION(BlueprintCallable, Category = "TileMap")
	void Clear();

private:
	class UHashedTileSet* HashTiles;

	class UGeneretionHashMap* GenMap;

	class TSubclassOf<APaperSpriteActor> GetBindActor(FPaperTileInfo Tile);

	TArrayInt3D         DefaultHashedMap;

	TArray<TArrayInt3D> HashedPatterns;
};
