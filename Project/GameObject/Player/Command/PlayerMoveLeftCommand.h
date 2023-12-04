#pragma once
#include"IPlayerCommand.h"

class PlayerMoveLeftCommand : public IPlayerCommand
{
public:

	void Exec(Player& player)override;

private:

};
