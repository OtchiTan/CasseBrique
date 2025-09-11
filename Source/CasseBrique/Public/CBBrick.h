#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CBBrick.generated.h"

class ACBGameManager;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHealthChanged);

UCLASS()
class CASSEBRIQUE_API ACBBrick : public AActor
{
	GENERATED_BODY()

public:
	ACBBrick();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* StaticMesh = nullptr;

	UPROPERTY()
	TWeakObjectPtr<ACBGameManager> GameManager = nullptr;

	UFUNCTION()
	void EventHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	int32 Health = 3;

	UPROPERTY(Blueprintable, BlueprintCallable, BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;

	bool bCanBeHit = true;
};
