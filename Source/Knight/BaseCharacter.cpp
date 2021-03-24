// Copyright Epic Games, Inc. All Rights Reserved.

#include "BaseCharacter.h"


DEFINE_LOG_CATEGORY_STATIC(SideScrollerCharacter, Log, All);

//////////////////////////////////////////////////////////////////////////
// ABaseCharacter

ABaseCharacter::ABaseCharacter()
{
	// Use only Yaw from the controller and ignore the rest of the rotation.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	// Set the size of our collision capsule.
	GetCapsuleComponent()->SetCapsuleHalfHeight(96.0f);
	GetCapsuleComponent()->SetCapsuleRadius(40.0f);

	// Configure character movement
	GetCharacterMovement()->GravityScale = 2.0f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.0f;
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	GetCharacterMovement()->MaxFlySpeed = 600.0f;

	// Lock character motion onto the XZ plane, so the character can't move in or out of the screen
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->SetPlaneConstraintNormal(FVector(0.0f, -1.0f, 0.0f));

	// Behave like a traditional 2D platformer character, with a flat bottom instead of a curved capsule bottom
	// Note: This can cause a little floating when going up inclines; you can choose the tradeoff between better
	// behavior on the edge of a ledge versus inclines by setting this to true or false
	GetCharacterMovement()->bUseFlatBaseForFloorChecks = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;

	//Sounds
	ActionSound = CreateDefaultSubobject<UAudioComponent>(TEXT("ActionSound"));
	ActionSound->SetupAttachment(RootComponent);

	Status = CharacterStatus::NONE;
	BeginTimer = 1.0;
	HurtTimer = 1.0;


	// Enable replication on the Sprite component so animations show up when networked
	// GetSprite()->SetIsReplicated(true);
	// bReplicates = true;
}

void ABaseCharacter::BeginPlay()
{
	Status = CharacterStatus::Spawned;

	Health = MaxHealth;

	Super::BeginPlay();

	DisableInput(GetController<APlayerController>());

	SetAnimState(IdleState);

	GetWorldTimerManager().SetTimer(BeginTimerHandle, this, &ABaseCharacter::ActiveCharacter, BeginTimer);
}


//////////////////////////////////////////////////////////////////////////
//Status
TEnumAsByte<CharacterStatus> ABaseCharacter::GetStatus() {
	return Status;
}

void ABaseCharacter::ActiveCharacter()
{
	if (Status == CharacterStatus::Spawned || Status == CharacterStatus::Passive)
	{
		Status = CharacterStatus::Active;
		EnableInput(GetController<APlayerController>());

		Actived();
	}
}

void ABaseCharacter::DeactiveCharacter()
{
	if (Status == CharacterStatus::Active)
	{
		Status = CharacterStatus::Passive;
		DisableInput(GetController<APlayerController>());
		SetAnimState(IdleState);

		Deactived();
	}
}

int ABaseCharacter::GetHealth()
{
	return Health;
}

void ABaseCharacter::DamageCharacter(int Damage)
{
	if (Damage < 0)
		Damage = 0;

	if (Damage > Health)
		Damage = Health;

	if (Damaged(Damage))
	{
		OnHurted();

		if (Health <= 0)
		{
			KillCharacter();
		}
		else
		{
			DeactiveCharacter();

			SetAnimState(HurtState);

			GetWorldTimerManager().SetTimer(HurtTimerHandle, this, &ABaseCharacter::EndHurt, HurtTimer);
		}
	}
}

void ABaseCharacter::EndHurt()
{
	SetAnimState(IdleState);

	ActiveCharacter();
}

void ABaseCharacter::KillCharacter()
{
	if (Status == CharacterStatus::Active)
	{
		Status = CharacterStatus::Killed;
		DisableInput(GetController<APlayerController>());

		OnKilled();

		SetAnimState(KillState, false);
		GetCapsuleComponent()->SetCollisionProfileName("OverlapAll");
		GetCapsuleComponent()->UpdateCollisionProfile();
	}
}

bool ABaseCharacter::Damaged(int Damage)
{
	Health -= Damage;
	return true;
}



void ABaseCharacter::Actived()
{
}

void ABaseCharacter::Deactived()
{
}

void ABaseCharacter::OnHurted_Implementation()
{
}
void ABaseCharacter::OnKilled_Implementation()
{
}

//////////////////////////////////////////////////////////////////////////
// Animation

void ABaseCharacter::SetAnimState(FAnimState State, bool looping)
{

	UPaperFlipbook* Animation = State.Animation;

	GetSprite()->SetFlipbook(State.Animation);
	GetSprite()->SetLooping(looping);

	if (ActionSound->Sound != State.Sound)
	{
		ActionSound->SetSound(State.Sound);
		ActionSound->Play();
	}
		
}

void ABaseCharacter::UpdateAnimation()
{
	const FVector PlayerVelocity = GetVelocity();
	const float PlayerWalkSpeed = PlayerVelocity.GetAbs().X;

	IsWalk = PlayerWalkSpeed > 0;
	IsFall = GetCharacterMovement()->IsFalling();

	float TravelDirection = PlayerVelocity.X;
	// Set the rotation so that the character faces his direction of travel.

	
	if (TravelDirection < 0.0f)
	{
		GetSprite()->SetRelativeRotation(FRotator(0.0, 180.0f, 0.0f));
		IsLeftDirect = true;
	}
	else if(TravelDirection > 0.0f)
	{
		GetSprite()->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
		IsLeftDirect = false;
	}

	if (GetStatus() == CharacterStatus::Active) {
		UpdateAnimState();

		if(IsIdle())
			SetAnimState(IdleState);
	}
}

void ABaseCharacter::UpdateAnimState()
{
}

bool ABaseCharacter::IsIdle()
{
	return true;
}

void ABaseCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	UpdateCharacter();
}


//////////////////////////////////////////////////////////////////////////
// Input

void ABaseCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	
}

void ABaseCharacter::MoveRight(float Value)
{
	/*UpdateChar();*/

	// Apply the input to the character motion
	AddMovementInput(FVector(1.0f, 0.0f, 0.0f), Value);
}

void ABaseCharacter::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	// Jump on any touch
	Jump();
}

void ABaseCharacter::TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	// Cease jumping once touch stopped
	StopJumping();
}

void ABaseCharacter::UpdateCharacter()
{
	UpdateAnimation();
}


