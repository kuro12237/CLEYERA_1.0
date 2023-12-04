#pragma once
#include"IScene.h"
#include"GameManager.h"
#include"Input.h"
#include"AudioManager.h"
#include"FileLoader.h"
#include"CollisionManager.h"
#include"Particle/Particle.h"
#include"ModelManager.h"

#include"GameObject/Player/Player.h"
#include"GameObject/Player/InputHandler/PlayerInputHandler.h"

class PgScene :public IScene
{
public:
    PgScene() {};
	~PgScene() {};


	void Initialize()override;

	void Update(GameManager* Scene)override;

	void Back2dSpriteDraw()override;
	void Object3dDraw()override;
	void Flont2dSpriteDraw()override;

private:
	ViewProjection view_{};

	PlayerInputHandler* playerInputHandler_ = nullptr;
	Player* player_ = nullptr;
	IPlayerCommand* playerCommand_ = nullptr;

};