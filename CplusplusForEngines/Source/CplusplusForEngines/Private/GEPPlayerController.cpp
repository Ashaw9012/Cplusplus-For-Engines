#include "GEPPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "GEPchar.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"

AGEPPlayerController::AGEPPlayerController() : Super()
{
	
}

void AGEPPlayerController::Init_Implementation()
{
	if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0); 
	}

	if (GetPawn() != nullptr)
	{
		GetPawn()->Destroy();
	}
}

void AGEPPlayerController::Handle_MatchStarted_Implementation()
{
	UWorld* const world = GetWorld();

	//find the player type and return a player spawn location
	AActor* tempStart = UGameplayStatics::GetGameMode(world)->FindPlayerStart(this);
	FVector spawnLocation = tempStart != nullptr ? tempStart-> GetActorLocation() : FVector::ZeroVector;
	FRotator spawnRotation = tempStart != nullptr ? tempStart-> GetActorRotation() : FRotator::ZeroRotator;
	FActorSpawnParameters spawnParams;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	APawn* tempPawn = world->SpawnActor<APawn>(_PawnToSpawn, spawnLocation, spawnRotation, spawnParams);
	Possess(tempPawn);

	//cast pawn to type and stores if successful run IF 
	if(AGEPchar* castedPawn = Cast<AGEPchar>(tempPawn))
	{
		//TODO: Bind to any relevant events
		castedPawn->Init(); 
	}
}

void AGEPPlayerController::Handle_MatchEnded_Implementation()
{
	//SetTnputMode(FInputmodeUIonly());
}
