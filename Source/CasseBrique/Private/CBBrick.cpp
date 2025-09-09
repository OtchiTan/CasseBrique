#include "CBBrick.h"

#include "CBBall.h"
#include "CBGameState.h"
#include "CBGameManager.h"


ACBBrick::ACBBrick()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));

	RootComponent = StaticMesh;
}

void ACBBrick::BeginPlay()
{
	Super::BeginPlay();

	OnActorHit.AddDynamic(this, &ACBBrick::EventHit);
}

void ACBBrick::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACBBrick::EventHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	ACBBall* Ball = Cast<ACBBall>(OtherActor);
	if (!IsValid(Ball) || !bCanBeHit)
		return;

	bCanBeHit = false;

	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::FromInt(Ball->BallDamage));

	Health -= Ball->BallDamage;

	Ball->BallDamage = 1;

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]
	{
		bCanBeHit = true;
	}, 0.2f, false);

	if (Health > 0)
	{
		OnHealthChanged.Broadcast();
		return;
	}

	if (ACBGameState* GameState = Cast<ACBGameState>(GetWorld()->GetGameState()))
		GameState->IncreasePlayerScore(1000);

	GameManager->Bricks.Remove(this);

	if (GameManager->Bricks.IsEmpty())
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Green, "Win");

	FTimerHandle DestroyTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(DestroyTimerHandle, [this]
	{
		Destroy();
	}, 0.2f, false);
}
