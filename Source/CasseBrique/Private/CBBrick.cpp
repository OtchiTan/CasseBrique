#include "CBBrick.h"

#include "CBBall.h"
#include "CBGameState.h"
#include "CBGameManager.h"
#include "Kismet/GameplayStatics.h"

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

void ACBBrick::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACBBrick::EventHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	const ACBBall* Ball = Cast<ACBBall>(OtherActor);
	if (!IsValid(Ball) || !bCanBeHit)
		return;

	bCanBeHit = false;
	
	Health -= Ball->BallDamage;

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

	GameManager->CheckWin();

	UGameplayStatics::PlaySound2D(GetWorld(), DestroySound);

	StaticMesh->SetSimulatePhysics(true);

	OnBrickDestroyed();
}

void ACBBrick::OnBrickDestroyed_Implementation()
{
}
