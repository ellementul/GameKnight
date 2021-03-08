// Copyright Epic Games, Inc. All Rights Reserved.

#include "BaseCharacter.h"
#include "PaperFlipbookComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Camera/CameraComponent.h"

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

	// Create a camera boom attached to the root (capsule)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 500.0f;
	CameraBoom->SocketOffset = FVector(0.0f, 0.0f, 75.0f);
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));


	// Create an orthographic camera (no perspective) and attach it to the boom
	SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	SideViewCameraComponent->ProjectionMode = ECameraProjectionMode::Orthographic;
	SideViewCameraComponent->OrthoWidth = 2048.0f;
	SideViewCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	// Prevent all automatic rotation behavior on the camera, character, and camera component
	CameraBoom->SetUsingAbsoluteRotation(true);
	SideViewCameraComponent->bUsePawnControlRotation = false;
	SideViewCameraComponent->bAutoActivate = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;

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

	//Sounds
	ActionSound = CreateDefaultSubobject<UAudioComponent>(TEXT("ActionSound"));
	ActionSound->SetupAttachment(RootComponent);

	Status = CharacterStatus::NONE;
	BeginTimer = 1.0;
	HurtTimer  = 1.0;

	// Enable replication on the Sprite component so animations show up when networked
	// GetSprite()->SetIsReplicated(true);
	// bReplicates = true;
}

void ABaseCharacter::BeginPlay()
{
	Status = CharacterStatus::Spawned;

	Super::BeginPlay();

	DisableInput(GetController<APlayerController>());

	GetWorldTimerManager().SetTimer(BeginTimerHandle, this, &ABaseCharacter::ActiveCharacter, BeginTimer);
}


//////////////////////////////////////////////////////////////////////////
//Status
TEnumAsByte<CharacterStatus> ABaseCharacter::GetStatus() {
	return Status;
}

void ABaseCharacter::ActiveCharacter()
{
	if (Status == CharacterStatus::Spawned || Status == CharacterStatus::Passive || Status == CharacterStatus::Hurted)
	{
		Status = CharacterStatus::Active;
		EnableInput(GetController<APlayerController>());
	}
}

bool ABaseCharacter::CharacterOn()
{
	if (Status == CharacterStatus::Passive || Status == CharacterStatus::Hurted)
	{
		Status = CharacterStatus::Active;

		return true;
	}

	return false;
}

bool ABaseCharacter::CharacterOff()
{
	if (Status == CharacterStatus::Active)
	{
		Status = CharacterStatus::Passive;

		return true;
	}

	return false;
}

bool ABaseCharacter::HurtCharacter()
{
	if (Status == CharacterStatus::Active)
	{
		Status = CharacterStatus::Hurted;

		DisableInput(GetController<APlayerController>());

		GetWorldTimerManager().SetTimer(HurtTimerHandle, this, &ABaseCharacter::ActiveCharacter, HurtTimer);

		return true;
	}

	return false;
}

bool ABaseCharacter::KillCharacter()
{
	if (Status == CharacterStatus::Active)
	{
		Status = CharacterStatus::Killed;

		return true;
	}

	return false;
}


void ABaseCharacter::OnHurted_Implementation()
{

}

void ABaseCharacter::OnKilled_Implementation()
{

}

//////////////////////////////////////////////////////////////////////////
// Animation

void ABaseCharacter::UpdateAnimation()
{
	const FVector PlayerVelocity = GetVelocity();
	const float PlayerWalkSpeed = PlayerVelocity.GetAbs().X;

	// Are we moving or standing still?
	UPaperFlipbook* DesiredAnimation = (PlayerWalkSpeed > 0.0f) ? RunningAnimation : IdleAnimation;
	DesiredAnimation = GetCharacterMovement()->IsFalling() ? FallingAnimation : DesiredAnimation;

	if (GetSprite()->GetFlipbook() != DesiredAnimation)
	{
		GetSprite()->SetFlipbook(DesiredAnimation);
	}

	if (GetSprite()->GetFlipbook() != RunningAnimation && WalkSound)
	{
		ActionSound->SetSound(WalkSound);
		ActionSound->Play();
	}

	float TravelDirection = PlayerVelocity.X;
	// Set the rotation so that the character faces his direction of travel.
	if (Controller != nullptr)
	{
		if (TravelDirection < 0.0f)
		{
			Controller->SetControlRotation(FRotator(0.0, 180.0f, 0.0f));
		}
		else if (TravelDirection > 0.0f)
		{
			Controller->SetControlRotation(FRotator(0.0f, 0.0f, 0.0f));
		}
	}
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
	// Update animation to match the motion
	UpdateAnimation();

}


