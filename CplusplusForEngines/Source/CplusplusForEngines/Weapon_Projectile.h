#pragma once

#include "CoreMinimal.h"
#include "CplusplusForEnginesProjectile.h"
#include "Weapon_Base.h"
#include "GameFramework/Actor.h"
#include "Weapon_Projectile.generated.h"

UCLASS(Abstract)
class CPLUSPLUSFORENGINES_API AWeapon_Projectile : public AWeapon_Base
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TSubclassOf<ACplusplusForEnginesProjectile> _projectile;
	
public:
	virtual bool Fire_Implementation() override;
};
