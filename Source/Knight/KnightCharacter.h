// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "KnightCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AKnightCharacter : public ABaseCharacter
{
	GENERATED_BODY()

	AKnightCharacter();

	/** Side view camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* SideViewCameraComponent;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	FVector RelativeLocationCamera;

	void MovingCamera(float DeltaSeconds);


protected:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface

	virtual void UpdateAnimState() override;
	virtual bool IsIdle() override;

	virtual bool Damaged(int Damage) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	FAnimState WalkState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	FAnimState JumpState;

public:

	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterCamera)
	FVector ShiftLocationCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterCamera)
	float CameraSpeed;

	UFUNCTION(BlueprintCallable, Category = Character)
	void BeginSpeak();

	UFUNCTION(BlueprintCallable, Category = Character)
	void EndSpeak();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CharacterStatus)
	bool IsSpeak;
};