

#include "KnightCharacter.h"

AKnightCharacter::AKnightCharacter()
{
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

	ShiftLocationCamera = FVector(150.0, 0.0, 150.0);
	CameraSpeed = 400.0;

	MaxHealth = 3;
}

void AKnightCharacter::BeginPlay()
{
	Super::BeginPlay();

	RelativeLocationCamera = SideViewCameraComponent->GetRelativeLocation();
}

void AKnightCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	MovingCamera(DeltaSeconds);
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

void AKnightCharacter::MovingCamera(float DeltaSeconds)
{
	USpringArmComponent* CameraArm = GetCameraBoom();

	FVector CurrentShiftLocationCamera = FVector(0.0, 0.0, 0.0);
	CurrentShiftLocationCamera.X += IsLeftDirect ? -1.0 * ShiftLocationCamera.X : ShiftLocationCamera.X;
	CurrentShiftLocationCamera.Z += IsFall ? ShiftLocationCamera.Z : 0;

	FVector CurrentLocation  = CameraArm->GetRelativeLocation();
	FVector NextLocation     = RelativeLocationCamera + CurrentShiftLocationCamera;
	FVector DeltaLocation    = NextLocation - CurrentLocation;

	FVector FractDeltaLocation = FVector(CameraSpeed, CameraSpeed, CameraSpeed);
	FractDeltaLocation *= DeltaLocation.GetSignVector();
	FractDeltaLocation *= DeltaSeconds;

	if (DeltaLocation.GetAbs().X > FractDeltaLocation.GetAbs().X)
	{
		CameraArm->AddRelativeLocation( FVector(FractDeltaLocation.X, 0.0, 0.0) );
	}

	if (DeltaLocation.GetAbs().Z > FractDeltaLocation.GetAbs().Z)
	{
		CameraArm->AddRelativeLocation( FVector(0.0, 0.0, FractDeltaLocation.Z) );
	}
}

void AKnightCharacter::UpdateAnimState()
{

	if (IsWalk) {
		SetAnimState(WalkState);
	}

	if (IsFall) {
		SetAnimState(JumpState);
	}
}

bool AKnightCharacter::IsIdle()
{
	return !(IsWalk || IsFall);
}

bool AKnightCharacter::Damaged(int Damage)
{
	int OldHealth = Health;

	if (GetStatus() == CharacterStatus::Active)
	{
		Health -= Damage;
	}

	return (Health != OldHealth);
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