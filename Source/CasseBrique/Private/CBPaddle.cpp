#include "CBPaddle.h"

#include "CBBall.h"
#include "CBPlayerController.h"
#include "EnhancedInputSubsystems.h"

#include "EnhancedInputComponent.h"


ACBPaddle::ACBPaddle()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));

	RootComponent = BoxComponent;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));

	StaticMesh->SetupAttachment(BoxComponent);
}

void ACBPaddle::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<ACBPlayerController>(Controller);
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem
		= ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}
}

void ACBPaddle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GEngine->AddOnScreenDebugMessage(-1, 0.f, bParrying ? FColor::Green : FColor::Red, "Parry");
}

void ACBPaddle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Move Bar
		EnhancedInputComponent->BindAction(MoveBarAction, ETriggerEvent::Triggered, this, &ACBPaddle::MoveBar);

		EnhancedInputComponent->BindAction(ParryAction, ETriggerEvent::Triggered, this, &ACBPaddle::Parry);
	}
}

void ACBPaddle::MoveBar(const FInputActionValue& Value)
{
	MoveBarYValue = Value.Get<float>();
	
	if (PlayerController->bShowMouseCursor)
		return;

	const float Offset = Value.Get<float>() * MovementSpeed;
	const float NextPosition = StaticMesh->GetRelativeLocation().Y + Offset;
	if (NextPosition > -MaxBarMovement && NextPosition < MaxBarMovement)
	{
		StaticMesh->AddLocalOffset(FVector(0, Offset, 0));

		if (Ball.IsValid())
		{
			Ball->SetActorLocation(StaticMesh->GetComponentLocation() + FVector(125, 0, 0));
		}
	}
}

void ACBPaddle::Parry(const FInputActionValue& Value)
{
	if (PlayerController->bShowMouseCursor)
		return;
	
	if (Ball.IsValid())
	{
		Ball->StaticMesh->SetSimulatePhysics(true);
		const float Y = MoveBarYValue * 550.f;
		Ball->StaticMesh->SetPhysicsLinearVelocity(FVector(1000, Y, 0));
		Ball.Reset();
		return;
	}

	if (bParrying)
		return;

	bParrying = true;
	GetWorld()->GetTimerManager().SetTimer(ParryTimerHandle, [this]
	{
		bParrying = false;
	}, ParryWindowTiming, false);
}
