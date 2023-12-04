#include "PlayerMoveRightCommand.h"

void PlayerMoveRightCommand::Exec(Player& player)
{
	player.MoveRight();
}
