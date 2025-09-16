#include "CBBall.h"

#include "CBPaddle.h"
#include "Kismet/KismetMathLibrary.h"

ACBBall::ACBBall()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;
}

void ACBBall::BeginPlay()
{
	Super::BeginPlay();

	OnActorHit.AddDynamic(this, &ACBBall::EventHit);
}

void ACBBall::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	StaticMesh->SetPhysicsLinearVelocity(Direction * BallSpeed);
}

void ACBBall::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ACBBall::EventHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	FVector MirroredDirection = UKismetMathLibrary::MirrorVectorByNormal(
		Direction, FVector(Hit.Normal.X, Hit.Normal.Y, 0.f));

	UKismetMathLibrary::Vector_Normalize(MirroredDirection, 0.0001);

	Direction = MirroredDirection;

	BallSpeed += 10.f;

	if (const ACBPaddle* Bar = Cast<ACBPaddle>(OtherActor))
	{
		BallDamage = Bar->bParrying ? 3 : 1;
		OnDamageChange.Broadcast();
	}
}
