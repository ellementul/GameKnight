// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "KnightCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AKnightCharacter : public ABaseCharacter
{
	GENERATED_BODY()

	AKnightCharacter();


protected:

	virtual void BeginPlay() override;

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface

	virtual void UpdateAnimState();
	virtual bool IsIdle();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	FAnimState WalkState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	FAnimState JumpState;

public:

	UFUNCTION(BlueprintCallable, Category = Character)
	void BeginSpeak();

	UFUNCTION(BlueprintCallable, Category = Character)
	void EndSpeak();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CharacterStatus)
	bool IsSpeak;
};