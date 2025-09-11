#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "CBGameState.generated.h"

class ACBGameManager;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScoreChanged, int32, NewScore);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthLose, int32, HealthLose);

UCLASS()
class CASSEBRIQUE_API ACBGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	int32 Score = 0;

	UPROPERTY(Blueprintable, BlueprintCallable, BlueprintAssignable)
	FOnScoreChanged OnScoreChanged;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Health = 3;

	UFUNCTION(BlueprintCallable)
	void IncreasePlayerScore(const int32 NewScore);

	UFUNCTION(BlueprintCallable)
	void DecreaseHealth();

	UPROPERTY(Blueprintable, BlueprintCallable, BlueprintAssignable)
	FOnHealthLose OnHealthLose;

	UPROPERTY(BlueprintReadOnly)
	TWeakObjectPtr<ACBGameManager> GameManager = nullptr;
};
