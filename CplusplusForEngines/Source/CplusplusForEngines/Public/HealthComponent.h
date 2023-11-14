// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FComponentDeadSignature, AController*, causer); 

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPLUSPLUSFORENGINES_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable, Category= "Components")
	FComponentDeadSignature onComponentDead; 
protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category= "Health")
	float m_CurrentHealth;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category= "Health")
	float m_MaxHealth; 

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category= "Shield")
	float m_CurrentShield;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category= "Shield")
	float m_MaxShield;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category= "Shield")
	bool m_CanRegenShield;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category= "Shield")
	float m_ShieldRecoverDelayTimer;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category= "Shield")
	float m_shieldRecoverRate;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category= "Shield")
	float m_shieldRecoverDelay; 
	
	virtual void BeginPlay() override;

	//function needed to bind to an event
	UFUNCTION()
	void DamageTaken(AActor* damagedActor, float damage, const UDamageType* damagetype, AController* instigator, AActor* causer);
};
