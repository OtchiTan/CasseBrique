#include "CBGameManager.h"

#include "CBBrick.h"
#include "CBGameState.h"


ACBGameManager::ACBGameManager()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
}

void ACBGameManager::BeginPlay()
{
	Super::BeginPlay();

	ACBGameState* GameState = Cast<ACBGameState>(GetWorld()->GetGameState());
	GameState->GameManager = this;

	SpawnBricks();
}

void ACBGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACBGameManager::SpawnBricks()
{
	for (const TWeakObjectPtr<ACBBrick>& Brick : Bricks)
	{
		Brick->Destroy();
	}

	Bricks.Empty();

	for (int X = -SizeX; X <= SizeX; ++X)
	{
		const bool bIsEvenRow = X % 2 == 0;
		for (int Y = -SizeY; Y <= (!bIsEvenRow ? SizeY : SizeY - 1); ++Y)
		{
			FVector Location = FVector(0);
			Location.X = X * 150.f;
			Location.Y = Y * 350.f;
			if (bIsEvenRow)
				Location.Y += 175.f;
			ACBBrick* Brick = GetWorld()->SpawnActor<ACBBrick>(BrickClass, Location, FRotator(0, 0, 0),
			                                                   FActorSpawnParameters());
			Brick->GameManager = this;
			Bricks.Add(Brick);
		}
	}
}

void ACBGameManager::CheckWin()
{
	if (!Bricks.IsEmpty())
		return;

	OnWin.Broadcast();
}
