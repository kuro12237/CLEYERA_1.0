#pragma once
#include"IPlayerCommand.h"

class PlayerMoveRightCommand : public IPlayerCommand
{
public:

	void Exec(Player& player)override;

private:

};

