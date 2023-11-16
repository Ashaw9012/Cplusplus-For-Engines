#include "GEPchar.h"
#include "AITypes.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"


AGEPchar::AGEPchar()
{
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.f);

	_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT ("Camera"));
	_Camera->SetupAttachment(GetCapsuleComponent());
	_Camera->SetRelativeLocation(FVector(-10.f, 0.f, 60.f));
	_Camera->bUsePawnControlRotation = true;

	_WeaponAttachPoint = CreateDefaultSubobject<USceneComponent>(TEXT("WeaponAttachPoint"));
	_WeaponAttachPoint->SetupAttachment(_Camera);
}

void AGEPchar::BeginPlay()
{
	Super::BeginPlay();
}

void AGEPchar::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if(Controller != nullptr)
	{
			AddMovementInput(GetActorForwardVector(), MovementVector.Y);
			AddMovementInput(GetActorRightVector(), MovementVector.X); 
	}
}

void AGEPchar::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if(Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AGEPchar::Shoot()
{
	
}

void AGEPchar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if(UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::StopJumping);

		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AGEPchar::Move);

		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AGEPchar::Look);
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Triggered, this, &AGEPchar::Shoot);
	}
}
