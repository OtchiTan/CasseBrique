#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "CBOutArea.generated.h"

UCLASS()
class CASSEBRIQUE_API ACBOutArea : public AActor
{
	GENERATED_BODY()

public:
	ACBOutArea();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* BoxCollisions = nullptr;

	UFUNCTION()
	void EventHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);
};
