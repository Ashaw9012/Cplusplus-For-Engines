#pragma once

#include "CoreMinimal.h"
#include "Weapon_Base.h"
#include "GameFramework/Actor.h"
#include "Weapon_Hitscan.generated.h"

UCLASS(Abstract)
class CPLUSPLUSFORENGINES_API AWeapon_Hitscan : public AWeapon_Base
{
	GENERATED_BODY()
	
public:
	virtual bool Fire_Implementation() override;
};
