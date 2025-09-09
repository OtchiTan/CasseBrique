#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "EnhancedInputSubsystemInterface.h"
#include "GameFramework/Pawn.h"
#include "CBPaddle.generated.h"

class ACBPlayerController;
class ACBBall;

UCLASS()
class CASSEBRIQUE_API ACBPaddle : public APawn
{
	GENERATED_BODY()

public:
	ACBPaddle();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UBoxComponent* BoxComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* StaticMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputMappingContext* InputMappingContext = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputAction* MoveBarAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputAction* ParryAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ParryWindowTiming = 2.f;
	
	UFUNCTION()
	void MoveBar(const FInputActionValue& Value);

	float MoveBarYValue = 0.f;

	UFUNCTION()
	void Parry(const FInputActionValue& Value);

	UPROPERTY(BlueprintReadWrite)
	TWeakObjectPtr<ACBBall> Ball = nullptr;

	UPROPERTY()
	TWeakObjectPtr<ACBPlayerController> PlayerController = nullptr;

	bool bParrying = false;

	FTimerHandle ParryTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxBarMovement = 1300.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MovementSpeed = 10.f;
};
