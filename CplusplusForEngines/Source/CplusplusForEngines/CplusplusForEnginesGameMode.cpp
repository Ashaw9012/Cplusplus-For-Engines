#include "CplusplusForEnginesGameMode.h"
#include "CplusplusForEnginesCharacter.h"
#include "GEPPlayerController.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

ACplusplusForEnginesGameMode::ACplusplusForEnginesGameMode()
	: Super()
{
	_CountdownTimer = 3;
	
}

AActor* ACplusplusForEnginesGameMode::FindPlayerStart_Implementation(AController* Player, const FString& IncomingName)
{
	if(_PlayerStarts.Num() == 0)
	{
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), _PlayerStarts);
	}
	if(_PlayerStarts.Num() > 0)
	{
		return _PlayerStarts[0];
	}
	return nullptr; 
}

void ACplusplusForEnginesGameMode::PostLogin(APlayerController* NewPlayer)
{
	_PlayerControllers.AddUnique(NewPlayer);
	if(AGEPPlayerController* castedPC = Cast<AGEPPlayerController>(NewPlayer))
	{
		//TODO: bind to any relevant events
		castedPC->Init(); 
	}
	
	Super::PostLogin(NewPlayer);
}

void ACplusplusForEnginesGameMode::Logout(AController* Exiting)
{
	_PlayerControllers.Remove(Exiting);
	Super::Logout(Exiting);
}

void ACplusplusForEnginesGameMode::DecreaseCountdown()
{
	_CountdownTimer--;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("%d"), _CountdownTimer));
	if(_CountdownTimer == 0)
	{
		StartMatch(); 
	}
	else
	{
		GetWorld()->GetTimerManager().SetTimer(_TimerDecreaseCountdown, this, &ACplusplusForEnginesGameMode::DecreaseCountdown, 1.f, false);
	}
}

void ACplusplusForEnginesGameMode::BeginPlay()
{
	Super::BeginPlay();

	//TODO: Add Gamerule Stuff here
}

void ACplusplusForEnginesGameMode::HandleMatchIsWaitingToStart()
{
	GetWorld()->GetTimerManager().SetTimer(_TimerDecreaseCountdown, this, &ACplusplusForEnginesGameMode::DecreaseCountdown, 1.f, false);
	Super::HandleMatchIsWaitingToStart();
}

void ACplusplusForEnginesGameMode::HandleMatchHasStarted()
{
	for (AController* controller : _PlayerControllers)
	{
		if(UKismetSystemLibrary::DoesImplementInterface(controller, UMatchStateHandler::StaticClass()))
		{
			IMatchStateHandler::Execute_Handle_MatchStarted(controller);
		}
	}
	
	Super::HandleMatchHasStarted();
}

void ACplusplusForEnginesGameMode::HandleMatchHasEnded()
{
	for (AController* controller : _PlayerControllers)
	{
		if(UKismetSystemLibrary::DoesImplementInterface(controller, UMatchStateHandler::StaticClass()))
		{
			IMatchStateHandler::Execute_Handle_MatchEnded(controller);
		}
	}
	Super::HandleMatchHasEnded();
}

void ACplusplusForEnginesGameMode::OnMatchStateSet()
{
	FString output;
	
	if(MatchState == MatchState::WaitingToStart)
	{
		output = "waiting to start";
	}
	else if (MatchState == MatchState::InProgress)
	{
		output = "In progress";
	}
	else if(MatchState == MatchState::InProgress)
	{
		output = "In progress";
	}
	else if (MatchState == MatchState::LeavingMap)
	{
		output = "Leaving map";
	}
	
	//shows the right message and puts it as a char array
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("State change to: %s"), *output));
	
	Super::OnMatchStateSet();
}

bool ACplusplusForEnginesGameMode::ReadyToStartMatch_Implementation()
{
	return false;
}

bool ACplusplusForEnginesGameMode::ReadyToEndMatch_Implementation()
{
	return false;
}
