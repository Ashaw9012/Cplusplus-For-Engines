#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "CplusplusForEnginesGameMode.generated.h"

UCLASS(minimalapi, Abstract)
class ACplusplusForEnginesGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ACplusplusForEnginesGameMode();

	virtual AActor* FindPlayerStart_Implementation(AController* Player, const FString& IncomingName) override;

	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;

protected:
	TArray<TObjectPtr<AActor>> _PlayerStarts;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<TObjectPtr<AController>> _PlayerControllers;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=MatchManagement)
	int _CountdownTimer;

	FTimerHandle _TimerDecreaseCountdown;
	UFUNCTION()
	void DecreaseCountdown();

	virtual void BeginPlay() override;

	virtual void HandleMatchIsWaitingToStart() override;
	virtual void HandleMatchHasStarted() override;
	virtual void HandleMatchHasEnded() override;

	virtual void OnMatchStateSet() override;

	virtual bool ReadyToStartMatch_Implementation() override;
	virtual bool ReadyToEndMatch_Implementation() override;
};



