#include "FirstObject.h"
#include "components/ArrowComponent.h"


AFirstObject::AFirstObject()
{
 	_Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = _Root;

	_Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	_Arrow->SetupAttachment(_Root);

	_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	_Mesh->SetupAttachment(_Root);

}

void AFirstObject::BeginPlay()
{
	Super::BeginPlay();
; 
}





