#pragma once
#include"IScene.h"
#include"GameManager.h"
#include"Input.h"
#include"AudioManager.h"
#include"FileLoader.h"
#include"CollisionManager.h"
#include"Particle/Particle.h"
#include"ModelManager.h"
#include"Light/Light.h"


class DebugScene:public IScene
{
public:
	DebugScene() {};
	~DebugScene();


	void Initialize()override;

	void Update(GameManager* Scene)override;

	void Back2dSpriteDraw()override;
	void Object3dDraw()override;
	void Flont2dSpriteDraw()override;
	
private:
	

	ViewProjection viewProjection{};

	unique_ptr<Sprite>sprite_ = nullptr;
	WorldTransform spriteWorldTransform_{};
	uint32_t SpritemobTexHandle_ = 0;
	uint32_t SpriteCLEYERATexHandle_ = 0;

	uint32_t Audiohandle = 0;
	uint32_t Audiohandle2 = 0;
	
	
	unique_ptr <Model>model_ = nullptr;
	WorldTransform modelWorldTransform_{};

	uint32_t houseModelHandle_ = 0;
	uint32_t packageModelHandle_ = 0;

	unique_ptr<Model>BallModel_ = nullptr;
	WorldTransform ballModelWorldTransform_ = {};

	unique_ptr<Model>testSkyDome_ = nullptr;
	WorldTransform testSkyDomeWorldTransform_ = {};

    PointLight_param pointLight_{};
	PointLight_param pointLightB_{};
	PointLight_param pointLightC_{};
};
