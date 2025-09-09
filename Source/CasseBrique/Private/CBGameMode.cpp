#include "CasseBrique/Public/CBGameMode.h"

#include "CBPaddle.h"
#include "CBGameState.h"
#include "CBPlayerController.h"

ACBGameMode::ACBGameMode()
{
	PlayerControllerClass = ACBPlayerController::StaticClass();
	DefaultPawnClass = ACBPaddle::StaticClass();
	GameStateClass = ACBGameState::StaticClass();
}
