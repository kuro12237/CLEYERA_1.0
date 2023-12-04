#include "DebugScene.h"

DebugScene::~DebugScene()
{
}

void DebugScene::Initialize()
{
	DebugCamera* debugCamera = new DebugCamera();
	debugCamera->Initialize();
	DebugTools::addCommand(debugCamera,"DebugCamera");

	viewProjection.Initialize({0,0,0.0f }, { 0.0f,0.0f,-10.0f });
	TextureManager::UnUsedFilePath();
	uint32_t SpritemobTexHandle = TextureManager::LoadTexture("Resources/Default/mob.png");
	TextureManager::UnUsedFilePath();
	uint32_t SpriteCLEYERATexHandle = TextureManager::LoadTexture("Resources/Default/CLEYERA.png");
	TextureManager::UnUsedFilePath();
	uint32_t uvTex = TextureManager::LoadTexture("Resources/Default/uvChecker.png");

	Vector2 mobsize = TextureManager::GetTextureSize(SpritemobTexHandle);
	mobsize;

	Audiohandle = AudioManager::SoundLoadWave("Resources/Sounds/SelectBGM.wav");
	Audiohandle2 = AudioManager::SoundLoadWave("Resources/Sounds/hit.wav");
	SpriteCLEYERATexHandle;
	sprite_ = make_unique<Sprite>();
	sprite_->SetTexHandle(SpritemobTexHandle);
	sprite_->Initialize(new SpriteBoxState,{-16,-16});
	
	sprite2_ = make_unique<Sprite>();
	sprite2_->SetTexHandle(uvTex);
	sprite2_->Initialize(new SpriteBoxState,{640,0},{320,320});
	
	sprite2_->SetSrc({ 0.0f,0.0f }, { 0,0.5f }, { 0.5f,0 }, { 0.5f,0.5f });

	sprite2WorldTransform_.Initialize();
	spriteWorldTransform_.Initialize();
	sprite2WorldTransform_.parent= &spriteWorldTransform_;

	modelWorldTransform_.Initialize();

	model_ = make_unique<Model>();
	model_->UseLight(HARF_LAMBERT);
	//model_->SetTexHandle(uvTex);
		//->Initialize(new ModelSphereState,{0,0,0},{10,0,0});

	PlaneModel_ = make_unique<Model>();
	PlaneModel_->SetTexHandle(uvTex);
	PlaneModel_->CreateModel(new ModelLineState, { 0,0,0 }, 1,{ 10,0,0 });
	modelPlaneWorldTranbsform_.Initialize();

	modelHandle_ = ModelManager::LoadObjectFile("House");

	model_->SetModel(modelHandle_);
	modelTexboxHandle_ = ModelManager::LoadObjectFile("package");

}

void DebugScene::Update(GameManager* Scene)
{
	Scene;

	ImGui::Begin("MainCamera");
	ImGui::DragFloat3("trans", &viewProjection.translation_.x, -0.2f, 0.2f);
	ImGui::DragFloat3("rotate", &viewProjection.rotation_.x, -0.1f, 0.1f);
	ImGui::End();

	ImGui::Begin("ModelTesr");

	ImGui::Text("ChangeModel :: o key");

	ImGui::End();


	model_->UseLight(HARF_LAMBERT);
	if (Input::PushKey(DIK_T))
	{
		model_->UseLight(NONE);
	}

	model_->SetModel(modelHandle_);
	TextureManager::UnUsedFilePath();

	if (Input::PushKey(DIK_O))
	{
		model_->SetModel(modelTexboxHandle_);
	}

#pragma region 
	
#pragma endregion


	modelWorldTransform_.UpdateMatrix();
	modelPlaneWorldTranbsform_.UpdateMatrix();

	DebugTools::UpdateExecute(0);
	viewProjection = DebugTools::ConvertViewProjection(viewProjection);

	viewProjection.UpdateMatrix();

}

void DebugScene::Back2dSpriteDraw()
{
}

void DebugScene::Object3dDraw()
{
	DebugTools::DrawExecute(0);
	model_->Draw(modelWorldTransform_, viewProjection);
	PlaneModel_->Draw(modelPlaneWorldTranbsform_, viewProjection);
}
void DebugScene::Flont2dSpriteDraw()
{
	//sprite_->Draw(spriteWorldTransform_,viewProjection);
	//sprite2_->Draw(sprite2WorldTransform_,viewProjection);
}

void DebugScene::Testparticle()
{

}


