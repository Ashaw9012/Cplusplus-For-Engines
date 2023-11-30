#include "GEPPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

AGEPPlayerController::AGEPPlayerController() : Super()
{
	
}

void AGEPPlayerController::Init_Implementation()
{
	if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0); 
	}
}

void AGEPPlayerController::Handle_MatchStarted_Implementation()
{
	IMatchStateHandler::Handle_MatchStarted_Implementation();
}

void AGEPPlayerController::Handle_MatchEnded_Implementation()
{
	IMatchStateHandler::Handle_MatchEnded_Implementation();
}
