#pragma once
#include"GameObject/Player/Player.h"
class Player;

class IPlayerCommand
{
public:

	~IPlayerCommand() {};

	virtual void Exec(Player& player) = 0;

private:

};