#include "PlayerMoveLeftCommand.h"

void PlayerMoveLeftCommand::Exec(Player& player)
{
	player.MoveLeft();
}
