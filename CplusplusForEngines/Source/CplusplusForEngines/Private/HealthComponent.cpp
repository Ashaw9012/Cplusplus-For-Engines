#include "HealthComponent.h"


UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	m_MaxHealth = 100.f;
	m_MaxShield = 100.0f;
	m_CanRegenShield = true;
	m_shieldRecoverRate = 10.f;
	m_shieldRecoverDelay = 2.f; 
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);
	m_CurrentHealth = m_MaxHealth;
	m_CurrentShield = m_MaxShield; 
}

void UHealthComponent::DamageTaken(AActor* damagedActor, float damage, const UDamageType* damagetype,
	AController* instigator, AActor* causer)
{
	//if damage is left over after the shield is depleted
	float leftOverDamage = FMath::Max(damage - m_CurrentShield, 0.f);
	//checks shield
	m_CurrentShield = FMath::Max(m_CurrentShield - damage, 0.f);
	m_ShieldRecoverDelayTimer = m_shieldRecoverDelay;

	//applies leftover damage if the shield is gone
	if(leftOverDamage > 0.f) {m_CurrentHealth = FMath::Max(m_CurrentShield - leftOverDamage, 0.f);}

	if(m_CurrentHealth <= 0.f) {onComponentDead.Broadcast(instigator);}
}


// Called every frame (update function)
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//stops nesting
	if(m_CurrentShield == m_MaxShield || !m_CanRegenShield) {return;}
	if(m_ShieldRecoverDelayTimer > 0.f)
	{
		m_ShieldRecoverDelayTimer -= DeltaTime;
	}
	else
	{
		//checks minimum shield and multiplies by delta time to start shield recovery 
		m_CurrentShield = FMath::Min(m_MaxShield, m_CurrentShield + (m_shieldRecoverRate * DeltaTime));
	}
	
}

