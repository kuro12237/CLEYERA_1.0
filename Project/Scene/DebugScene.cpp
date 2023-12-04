#include "DebugScene.h"

DebugScene::~DebugScene()
{
}

void DebugScene::Initialize()
{

	viewProjection.Initialize({0,0,0.0f }, { 0.0f,0.0f,-10.0f });

	//tex
	TextureManager::UnUsedFilePath();
	SpritemobTexHandle_ = TextureManager::LoadTexture("Resources/Default/mob.png");
	TextureManager::UnUsedFilePath();
	SpriteCLEYERATexHandle_ = TextureManager::LoadTexture("Resources/Default/CLEYERA.png");

	//audio
	Audiohandle = AudioManager::SoundLoadWave("Resources/Sounds/SelectBGM.wav");
	Audiohandle2 = AudioManager::SoundLoadWave("Resources/Sounds/hit.wav");
	
	//sprite
	sprite_ = make_unique<Sprite>();
	sprite_->SetTexHandle(SpritemobTexHandle_);
	sprite_->Initialize(new SpriteBoxState);
	spriteWorldTransform_.Initialize();

    //model
	model_ = make_unique<Model>();
	model_->UseLight(HARF_LAMBERT);
	modelWorldTransform_.Initialize();
	
	houseModelHandle_ = ModelManager::LoadObjectFile("House");
	model_->SetModel(houseModelHandle_);
	packageModelHandle_ = ModelManager::LoadObjectFile("package");

}

void DebugScene::Update(GameManager* Scene)
{
	Scene;

	ImGui::Begin("MainCamera");
	ImGui::DragFloat3("trans", &viewProjection.translation_.x, -0.2f, 0.2f);
	ImGui::DragFloat3("rotate", &viewProjection.rotation_.x, -0.1f, 0.1f);
	ImGui::End();

	ImGui::Begin("ModelTest");
	ImGui::Text("ChangeModel :: o key");
	ImGui::Text("UseLight :: L key");
	ImGui::End();

	ImGui::Begin("SpriteTest");
	ImGui::Text("ChangeTex :: I key");
	ImGui::End();

	model_->UseLight(HARF_LAMBERT);
	if (Input::PushKey(DIK_L))
	{
		model_->UseLight(NONE);
	}

	model_->SetModel(houseModelHandle_);
	if (Input::PushKey(DIK_O))
	{
		model_->SetModel(packageModelHandle_);
	}

	sprite_->SetTexHandle(SpritemobTexHandle_);
	if (Input::PushKey(DIK_I))
	{
		TextureManager::UnUsedFilePath();
		sprite_->SetTexHandle(SpriteCLEYERATexHandle_);
	}


	modelWorldTransform_.UpdateMatrix();
	spriteWorldTransform_.UpdateMatrix();
	viewProjection.UpdateMatrix();

}

void DebugScene::Back2dSpriteDraw()
{
}

void DebugScene::Object3dDraw()
{
	
	model_->Draw(modelWorldTransform_, viewProjection);

}
void DebugScene::Flont2dSpriteDraw()
{
	sprite_->Draw(spriteWorldTransform_,viewProjection);
}




