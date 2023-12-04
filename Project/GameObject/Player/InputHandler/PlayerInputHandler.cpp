#include "PlayerInputHandler.h"

IPlayerCommand* PlayerInputHandler::HandleInput()
{
	if (Input::PushKey(DIK_A))
	{
		return pressKeyA_;
	}else if (Input::PushKey(DIK_D))
	{
		return pressKeyD_;
	}
	return nullptr;
}

void PlayerInputHandler::AssignMoveLeftCommand2PreessKeyA()
{
	IPlayerCommand* command = new PlayerMoveLeftCommand();
	this->pressKeyA_ = command;
}

void PlayerInputHandler::AssignMoveRightCommand2PreessKeyD()
{
	IPlayerCommand* command = new PlayerMoveRightCommand();
	this->pressKeyD_ = command;
}
