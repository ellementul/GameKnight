// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "PaperFlipbookComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
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

	void EndHurt();

	virtual bool Damaged(int Damage);

	UFUNCTION(BlueprintNativeEvent, Category = HealthAndDamage)
	void OnHurted();
	virtual void OnHurted_Implementation();

	//Animation
	/** Called to choose the correct animation to play based on the character's movement state */
	void UpdateAnimation();
	virtual void UpdateAnimState();
	virtual bool IsIdle();

	bool IsLeftDirect = false;
	bool IsWalk       = false;
	bool IsFall       = false;

	void SetAnimState(FAnimState State, bool looping = true);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	FAnimState IdleState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	FAnimState HurtState;

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

	UFUNCTION(BlueprintCallable, Category = HealthAndDamage)
		void DamageCharacter(int Damage);
};
