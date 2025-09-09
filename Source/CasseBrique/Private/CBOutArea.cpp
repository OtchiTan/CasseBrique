#include "CBOutArea.h"

#include "CBBall.h"
#include "CBGameState.h"


ACBOutArea::ACBOutArea()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxCollisions = CreateDefaultSubobject<UBoxComponent>(FName("BoxCollisions"));

	RootComponent = BoxCollisions;
}

void ACBOutArea::BeginPlay()
{
	Super::BeginPlay();

	OnActorHit.AddDynamic(this, &ACBOutArea::EventHit);
}

void ACBOutArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACBOutArea::EventHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	if (ACBBall* Ball = Cast<ACBBall>(OtherActor))
	{
		Ball->Destroy();

		if (ACBGameState* GameState = Cast<ACBGameState>(GetWorld()->GetGameState()))
		{
			GameState->DecreaseHealth();
		}
	}
}
