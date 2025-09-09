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

void ACBBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACBBall::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ACBBall::EventHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	BallSpeed += 5.f;

	FVector LinearVelocity = StaticMesh->GetPhysicsLinearVelocity();

	LinearVelocity = UKismetMathLibrary::ClampVectorSize(LinearVelocity, BallSpeed, BallSpeed);

	StaticMesh->SetPhysicsLinearVelocity(LinearVelocity);

	const ACBPaddle* Bar = Cast<ACBPaddle>(OtherActor);

	if (Bar && Bar->bParrying)
	{
		BallDamage = 2;
	}
}
