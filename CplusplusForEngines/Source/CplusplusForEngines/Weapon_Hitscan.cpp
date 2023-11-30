#include "Weapon_Hitscan.h"

#include "components/ArrowComponent.h"
#include "Kismet/KismetSystemLibrary.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeapinHitscan, Display, All);

bool AWeapon_Hitscan::Fire_Implementation()
{
	UE_LOG(LogWeapinHitscan, Display, TEXT("FIREEEEEEEEEEEEEEEEEEEEEE HITSCAN"));

	UWorld* const world = GetWorld();
	if(world == nullptr) {return false;}

	FHitResult hit(ForceInit);
	FVector start = _Muzzle->GetComponentLocation();
	FVector end = start + (_Muzzle->GetForwardVector() * 1000);
	TArray<AActor*> ActorsToIgnore;

	//Hitscan system, it works by getting the start and end point making a line in a colour and then fires at the location
	if(UKismetSystemLibrary::LineTraceSingle(world, start, end, UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel2), false,
		ActorsToIgnore, EDrawDebugTrace::ForDuration, hit, true, FLinearColor::Red, FLinearColor::Green, 5))
	{
		UE_LOG(LogWeapinHitscan, Display, TEXT("Hit pos: %s"), *hit.ImpactPoint.ToString());
		
	}

	return true; 
}
