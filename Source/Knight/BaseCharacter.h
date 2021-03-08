// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "Components/AudioComponent.h"
#include "BaseCharacter.generated.h"

class UTextRenderComponent;

UENUM()

enum CharacterStatus {
	NONE    UMETA(DisplayName = "NONE"),
	Spawned UMETA(DisplayName = "Spawned"),
	Active  UMETA(DisplayName = "Active"),
	Passive UMETA(DisplayName = "Passive"),
	Hurted  UMETA(DisplayName = "Hurted"),
	Killed  UMETA(DisplayName = "Killed"),
};

/**
 * Base class for characters
 */
UCLASS(config = Game)
class ABaseCharacter : public APaperCharacter
{
	GENERATED_BODY()

	/** Side view camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* SideViewCameraComponent;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Sound, meta = (AllowPrivateAccess = "true"))
	class UAudioComponent* ActionSound;

private:
	TEnumAsByte<CharacterStatus> Status;

protected:

	virtual void BeginPlay() override;

	//Character Status

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Status")
	float BeginTimer;

	FTimerHandle BeginTimerHandle;

	void ActiveCharacter();

	UFUNCTION(BlueprintCallable, Category = Character)
	TEnumAsByte<CharacterStatus> GetStatus();

	UFUNCTION(BlueprintCallable, Category = Character)
	bool HurtCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Status")
	float HurtTimer;

	FTimerHandle HurtTimerHandle;
	
	UFUNCTION(BlueprintCallable, Category = Character)
	bool KillCharacter();

	UFUNCTION(BlueprintCallable, Category = Character)
	bool CharacterOff();

	UFUNCTION(BlueprintCallable, Category = Character)
	bool CharacterOn();


	UFUNCTION(BlueprintNativeEvent, Category = Character)
	void OnHurted();
	virtual void OnHurted_Implementation();

	UFUNCTION(BlueprintNativeEvent, Category = Character)
	void OnKilled();
	virtual void OnKilled_Implementation();


	//Animation
	// The animation to play while running around
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* RunningAnimation;

	// The animation to play while idle (standing still)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* IdleAnimation;
	//The animation pawn in 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* FallingAnimation;

	virtual void Tick(float DeltaSeconds) override;

	/** Called to choose the correct animation to play based on the character's movement state */
	void UpdateAnimation();

	/** Called for side to side input */
	void MoveRight(float Value);

	void UpdateCharacter();

	/** Handle touch inputs. */
	void TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location);

	/** Handle touch stop event. */
	void TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface

	//Sounds Character

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Sounds)
		class USoundBase* WalkSound;


public:
	ABaseCharacter();

	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
};
