#include "CBGameState.h"

void ACBGameState::IncreasePlayerScore(const int32 NewScore)
{
	Score += NewScore;

	OnScoreChanged.Broadcast(NewScore);
}

void ACBGameState::DecreaseHealth()
{
	Health--;

	OnHealthLose.Broadcast(Health);
}
