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
	model_->SetTexHandle(uvTex);
	model_->Initialize(new ModelSphereState,{0,0,0},{10,0,0});

	PlaneModel_ = make_unique<Model>();
	PlaneModel_->SetTexHandle(uvTex);
	PlaneModel_->Initialize(new ModelPlaneState, { 0,0,0 }, { 10,0,0 });
	modelPlaneWorldTranbsform_.Initialize();
	//model_->CreateFromObj("axis");
}

void DebugScene::Update(GameManager* Scene)
{
	ImGui::Begin("MainCamera");
	ImGui::SliderFloat3("trans", &viewProjection.translation_.x, -15, 15);
	ImGui::SliderFloat3("rotate", &viewProjection.rotation_.x, -1, 1);
	ImGui::End();

	ImGui::Begin("key");
	ImGui::Text("0 Pushkey PlayAudio");
	ImGui::Text("9 Pushkey StateChange");
	ImGui::End();

	ImGui::Begin("sphere");
	ImGui::DragFloat3("t", &modelWorldTransform_.translate.x, -0.5f, 0.5f);
	ImGui::DragFloat3("r", &modelWorldTransform_.rotation.x, -0.5f, 0.5f);
	ImGui::End();

	ImGui::Begin("plane");
	ImGui::DragFloat3("t", &modelPlaneWorldTranbsform_.translate.x,-0.5f, 0.5f);
	ImGui::DragFloat3("r", &modelPlaneWorldTranbsform_.rotation.x, -0.5f, 0.5f);
	ImGui::End();

	ImGui::Begin("Sprite");
	ImGui::ColorPicker4("color", &color.x);
	ImGui::DragFloat3("Rotate", &sprite2WorldTransform_.translate.x, 0.1f);
	ImGui::Checkbox("NONE", &NoneFlag);
	ImGui::Checkbox("Add", &AddFlag);
	ImGui::Checkbox("Subtract", &SubtractFlag);
	ImGui::Checkbox("Multiply", &MultiplyFlag);
	ImGui::Checkbox("Screen", &ScreenFlag);
	ImGui::End();

	if (Input::PushKeyPressed(DIK_S))
	{
		AudioManager::AudioPlayWave(Audiohandle);
		Flag = true;
	}
	if (Flag)
	{
		count++;
		//AudioManager::AudioVolumeControl(Audiohandle, count*2);
	}
	model_->UseLight(HARF_LAMBERT);
	if (Input::PushKey(DIK_T))
	{
		model_->UseLight(NONE);
	}


	if (count>180)
	{
		count = 0;
		AudioManager::AudioStopWave(Audiohandle);
		Flag = false;
	}
	if (Input::PushKeyPressed(DIK_D))
	{
		AudioManager::AudioPlayWave(Audiohandle2);

	}
	
#pragma region 
	{
		if (NoneFlag)
		{
			sprite_->SetBlendMode(BlendNone);
			AddFlag = false;
			SubtractFlag = false;
			MultiplyFlag = false;
			ScreenFlag = false;
		}
		if (AddFlag)
		{
			sprite_->SetBlendMode(BlendAdd);
			NoneFlag = false;
			SubtractFlag = false;
			MultiplyFlag = false;
			ScreenFlag = false;
		}
		if (SubtractFlag)
		{
			sprite_->SetBlendMode(BlendSubtruct);
			AddFlag = false;
			NoneFlag = false;
			MultiplyFlag = false;
			ScreenFlag = false;
		}
		if (MultiplyFlag)
		{
			sprite_->SetBlendMode(BlendMultiply);
			AddFlag = false;
			SubtractFlag = false;
			NoneFlag = false;
			ScreenFlag = false;
		}
		if (ScreenFlag)
		{
			sprite_->SetBlendMode(BlendScreen);
			AddFlag = false;
			SubtractFlag = false;
			MultiplyFlag = false;
			NoneFlag = false;
		}
	}
#pragma endregion

	sprite_->SetColor(color);
	Scene;

	if (Input::PushKey(DIK_D))
	{
		spriteWorldTransform_.translate.x += 32.1f;
	}
	if (Input::PushKey(DIK_A))
	{
		spriteWorldTransform_.translate.x -= 32.1f;
	}

	if (Input::PushKey(DIK_R))
	{
		spriteWorldTransform_.rotation.z += 0.1f;
	}

	spriteWorldTransform_.UpdateMatrix();
	sprite2WorldTransform_.UpdateMatrix();
	modelWorldTransform_.UpdateMatrix();
	modelPlaneWorldTranbsform_.UpdateMatrix();

	DebugTools::UpdateExecute(0);
	viewProjection.UpdateMatrix();
	//viewProjection = DebugTools::ConvertViewProjection(viewProjection);

}

void DebugScene::Back2dSpriteDraw()
{
}

void DebugScene::Object3dDraw()
{
	model_->Draw(modelWorldTransform_, viewProjection);
	PlaneModel_->Draw(modelPlaneWorldTranbsform_, viewProjection);
}
void DebugScene::Flont2dSpriteDraw()
{
	sprite_->Draw(spriteWorldTransform_,viewProjection);
	sprite2_->Draw(sprite2WorldTransform_,viewProjection);
}

void DebugScene::Testparticle()
{

}


