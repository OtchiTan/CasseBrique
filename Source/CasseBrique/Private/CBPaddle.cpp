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
}

void ACBPaddle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Move Bar
		EnhancedInputComponent->BindAction(MoveBarAction, ETriggerEvent::Triggered, this, &ACBPaddle::MoveBar);
	}
}

void ACBPaddle::MoveBar(const FInputActionValue& Value)
{
	if (PlayerController->bShowMouseCursor)
		return;

	const float Offset = Value.Get<float>() * MovementSpeed;
	const float NextPosition = StaticMesh->GetRelativeLocation().Y + Offset;
	if (NextPosition > -MaxBarMovement && NextPosition < MaxBarMovement)
	{
		StaticMesh->AddLocalOffset(FVector(0, Offset, 0));
	}
}

void ACBPaddle::Parry(const float MoveInputValue)
{
	if (PlayerController->bShowMouseCursor)
		return;

	if (Ball.IsValid())
	{
		Ball->DetachFromActor(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));
		Ball->StaticMesh->SetSimulatePhysics(true);
		const float Y = MoveInputValue;
		Ball->Direction = FVector(1, Y, 0);
		Ball.Reset();
		return;
	}

	if (bParryingCooldown)
		return;

	bParrying = true;
	bParryingCooldown = true;
	GetWorld()->GetTimerManager().SetTimer(ParryTimerHandle, [this]
	{
		bParrying = false;
		OnParryStateChange();
	}, ParryWindowTiming, false);
	GetWorld()->GetTimerManager().SetTimer(ParryCooldownHandle, [this]
	{
		bParryingCooldown = false;
		OnParryStateChange();
	}, ParryCooldownTiming, false);

	OnParryStateChange();
}
