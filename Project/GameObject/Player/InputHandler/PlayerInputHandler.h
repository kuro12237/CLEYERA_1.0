#pragma once
#include"GameObject/Player/Command/IPlayerCommand.h"
#include"GameObject/Player/Command/PlayerMoveLeftCommand.h"
#include"GameObject/Player/Command/PlayerMoveRightCommand.h"
#include"Input.h"

class PlayerInputHandler
{
public:

	IPlayerCommand* HandleInput();

	void AssignMoveLeftCommand2PreessKeyA();

	void AssignMoveRightCommand2PreessKeyD();

private:

	IPlayerCommand* pressKeyD_;
	IPlayerCommand* pressKeyA_;
};

