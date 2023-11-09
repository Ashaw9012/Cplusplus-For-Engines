#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FirstObject.generated.h"

class UArrowComponent;
class URotatingMovementComponent;

UCLASS(Abstract)
class CPLUSPLUSFORENGINES_API AFirstObject : public AActor
{
	GENERATED_BODY()
	
public:	
	AFirstObject();

	virtual void BeginPlay() override;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USceneComponent> _Root;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> _Mesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UArrowComponent> _Arrow;

};
