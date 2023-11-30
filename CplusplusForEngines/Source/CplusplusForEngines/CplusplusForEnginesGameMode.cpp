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
	
}

void ACplusplusForEnginesGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void ACplusplusForEnginesGameMode::HandleMatchIsWaitingToStart()
{
	Super::HandleMatchIsWaitingToStart();
}

void ACplusplusForEnginesGameMode::HandleMatchHasStarted()
{
	Super::HandleMatchHasStarted();
}

void ACplusplusForEnginesGameMode::HandleMatchHasEnded()
{
	Super::HandleMatchHasEnded();
}

void ACplusplusForEnginesGameMode::OnMatchStateSet()
{
	Super::OnMatchStateSet();
}

bool ACplusplusForEnginesGameMode::ReadyToStartMatch_Implementation()
{
	return Super::ReadyToStartMatch_Implementation();
}

bool ACplusplusForEnginesGameMode::ReadyToEndMatch_Implementation()
{
	return Super::ReadyToEndMatch_Implementation();
}
