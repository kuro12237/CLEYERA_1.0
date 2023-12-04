#include "StageScene.h"

void StageScene::Initialize()
{
	playerInputHandler_ = new PlayerInputHandler();
	playerInputHandler_->AssignMoveRightCommand2PreessKeyD();
	playerInputHandler_->AssignMoveLeftCommand2PreessKeyA();
	player_ = new Player();
	player_->Initialize();
	view_.Initialize();
}

void StageScene::Update(GameManager* Scene)
{
	Scene;
	playerCommand_ = playerInputHandler_->HandleInput();

	if (this->playerCommand_)
	{
		playerCommand_->Exec(*player_);
	}
	player_->Update();

	view_.UpdateMatrix();

}

void StageScene::Back2dSpriteDraw()
{
}

void StageScene::Object3dDraw()
{
	player_->Draw(view_);
}

void StageScene::Flont2dSpriteDraw()
{
}
