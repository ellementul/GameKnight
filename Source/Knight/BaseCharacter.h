// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "Components/AudioComponent.h"
#include "BaseCharacter.generated.h"

UENUM()

enum CharacterStatus {
	NONE    UMETA(DisplayName = "NONE"),
	Spawned UMETA(DisplayName = "Spawned"),
	Active  UMETA(DisplayName = "Active"),
	Passive UMETA(DisplayName = "Passive"),
	Killed  UMETA(DisplayName = "Killed"),
};

USTRUCT(BlueprintType)
struct FAnimState {

	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UPaperFlipbook* Animation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USoundBase* Sound;

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
	virtual void Tick(float DeltaSeconds) override;

	//Character Status

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Status")
	float BeginTimer;

	FTimerHandle BeginTimerHandle;

	UFUNCTION(BlueprintCallable, Category = Character)
	TEnumAsByte<CharacterStatus> GetStatus();

	void ActiveCharacter();
	void DeactiveCharacter();

	UFUNCTION(BlueprintCallable, Category = Character)
	void KillCharacter();
	
	virtual void Actived();
	virtual void Deactived();

	UFUNCTION(BlueprintNativeEvent, Category = Character)
	void OnKilled();
	virtual void OnKilled_Implementation();

	//Health and Damage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HealthAndDamage)
	int MaxHealth = 1;
	int Health    = 0;

	FTimerHandle HurtTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HealthAndDamage)
	float HurtTimer;

	UFUNCTION(BlueprintCallable, Category = HealthAndDamage)
	int GetHealth();

	UFUNCTION(BlueprintCallable, Category = HealthAndDamage)
	void DamgeCharacter(int Damage);
	void EndHurt();

	virtual void Damaged(int Damage);

	UFUNCTION(BlueprintNativeEvent, Category = HealthAndDamage)
	void OnHurted();
	virtual void OnHurted_Implementation();

	//Animation
	/** Called to choose the correct animation to play based on the character's movement state */
	void UpdateAnimation();
	virtual void UpdateAnimState();
	virtual bool IsIdle();

	bool IsWalk;
	bool IsFall;

	void SetAnimState(FAnimState State, bool looping = true);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	FAnimState IdleState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	FAnimState KillState;
	

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


public:
	ABaseCharacter();

	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
};
