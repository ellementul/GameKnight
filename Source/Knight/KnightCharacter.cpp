

#include "KnightCharacter.h"

AKnightCharacter::AKnightCharacter()
{
}

void AKnightCharacter::BeginPlay(){

	Super::BeginPlay();
}

void AKnightCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Note: the 'Jump' action and the 'MoveRight' axis are bound to actual keys/buttons/sticks in DefaultInput.ini (editable from Project Settings..Input)
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAxis("MoveRight", this, &AKnightCharacter::MoveRight);

	PlayerInputComponent->BindTouch(IE_Pressed, this, &AKnightCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AKnightCharacter::TouchStopped);
}

void ABaseCharacter::UpdateAnimState()
{

	if (IsWalk)
	{
		SetAnimState(WalkState);
	}

}

void AKnightCharacter::BeginSpeak()
{
	IsSpeak = true;
	DeactiveCharacter();
	
}

void AKnightCharacter::EndSpeak()
{
	IsSpeak = false;
	ActiveCharacter();
}
