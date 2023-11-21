#include "Weapon_Projectile.h"

#include "components/ArrowComponent.h"

DEFINE_LOG_CATEGORY_STATIC(logWeaponProj, Display, All);

bool AWeapon_Projectile::Fire_Implementation()
{
	UE_LOG(logWeaponProj, Display, TEXT("FIREEEEEEEEEEEEEEEEEEEEEE PROJECTILE CLASS"));

	UWorld* const world = GetWorld();
	if(world == nullptr || _projectile == nullptr) {return false;}
	FActorSpawnParameters spawnParams;
	spawnParams.Owner = GetOwner();
	spawnParams.Instigator = GetInstigator();
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	world->SpawnActor(_projectile, &_Muzzle->GetComponentTransform(), spawnParams);

	return true; 
}
