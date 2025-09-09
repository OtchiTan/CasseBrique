#pragma once

#include "CoreMinimal.h"
#include "CBBrick.h"
#include "GameFramework/Actor.h"
#include "CBGameManager.generated.h"

class ACBBrick;

UCLASS()
class CASSEBRIQUE_API ACBGameManager : public AActor
{
	GENERATED_BODY()

public:
	ACBGameManager();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	TSet<TWeakObjectPtr<ACBBrick>> Bricks = {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ACBBrick> BrickClass = ACBBrick::StaticClass();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SizeX = 3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SizeY = 3;
};
