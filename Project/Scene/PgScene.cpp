#include "PgScene.h"

void PgScene::Initialize()
{
	playerInputHandler_ = new PlayerInputHandler();
	playerInputHandler_->AssignMoveRightCommand2PreessKeyD();
	playerInputHandler_->AssignMoveLeftCommand2PreessKeyA();
	player_ = new Player();
	player_->Initialize();
	view_.Initialize();
}

void PgScene::Update(GameManager* Scene)
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

void PgScene::Back2dSpriteDraw()
{
}

void PgScene::Object3dDraw()
{
	player_->Draw(view_);
}

void PgScene::Flont2dSpriteDraw()
{
}
