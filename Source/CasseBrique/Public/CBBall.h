#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CBBall.generated.h"

UCLASS()
class CASSEBRIQUE_API ACBBall : public APawn
{
	GENERATED_BODY()

public:
	ACBBall();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMeshComponent* StaticMesh = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float BallSpeed = 1000.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 BallDamage = 1;

	FVector Direction = FVector::ZeroVector;

	UFUNCTION()
	void EventHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

};
