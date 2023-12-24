#include "DebugScene.h"

DebugScene::~DebugScene()
{
}

void DebugScene::Initialize()
{
	//winTitleの設定
	WinApp::SetTiTleName(L"2023/12/05/20:31 CLEYERA");

	viewProjection.Initialize({0,0,0.0f }, { 0.0f,2.0f,-12.0f });

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

	uint32_t ballTexHandle = TextureManager::LoadTexture("testBall.png");
    //model
	model_ = make_unique<Model>();
	model_->UseLight();
	modelWorldTransform_.Initialize();
	model_->SetTexHandle(ballTexHandle);
	//model_->CreateModel(make_unique<ModelSphereState>());
	
	//model_->CreateModel(make_unique<ModelSphereState>());
	
	houseModelHandle_ = ModelManager::LoadObjectFile("House");
	GroundModelHandle_ = ModelManager::LoadObjectFile("TestGround");
	uint32_t testSkydomeModelHandle_= ModelManager::LoadObjectFile("TestSkyDome");
	model_->SetModel(GroundModelHandle_);
	//handle読み込み
	//モデルにセットし
	//handleがきりかわるたびにハンドルに対応したモデルの頂点に作り変える


	BallModel_ = make_unique<Model>();
	BallModel_->UseLight();
	BallModel_->CreateModel(make_unique<ModelSphereState>());

	//BallModel_->CreateModel(make_unique<ModelSphereState>());
	BallModel_->SetTexHandle(ballTexHandle);

	ballModelWorldTransform_.Initialize();

	testSkyDome_ = make_unique<Model>();
	testSkyDome_->UseLight();
	testSkyDome_->SetModel(testSkydomeModelHandle_);
	testSkyDomeWorldTransform_.Initialize();
	testSkyDomeWorldTransform_.scale = { 10,10,10 };
	testSkyDomeWorldTransform_.UpdateMatrix();

	pointLight_.position = { -1.0f,2.0f,1.0f };
	pointLightB_.position = { 1.0f,2.0f,1.0f };
	pointLightC_.position = { 0.0f,2.0f,-1.0f };

	pointLight_.radious = 3.0f;
	pointLightB_.radious = 3.0f;
	pointLightC_.radious = 3.0f;

	pointLight_.color = { 1.0f,0.0f,0.0f,1.0f };
	pointLightB_.color = { 0.0f,1.0f,0.0f,1.0f };
	pointLightC_.color = { 0.0f,0.0f,1.0f,1.0f };

	pointLight_.intencity = 0;
	pointLightB_.intencity = 0;
	pointLightC_.intencity = 0;

	sunLight_.radious = 30.0f;
	sunLight_.position.y = 3.0f;
	fireParticle_ = make_unique<FireParticle>();
	fireParticle_->Initialize(pointFireLightPosition_);

	player_ = make_unique<Player>();
	player_->Initialize();

	enemy_ = make_unique<Enemy>();
	enemy_->Initialize();

	collisionManager = make_unique<CollisionManager>();
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



	//debug用でモデルを毎回切り替え挙動を確認
	model_->SetModel(GroundModelHandle_);
	if (!Input::PushKey(DIK_O))
	{
		model_->SetModel(houseModelHandle_);
	}


	ImGui::Begin("TestSphere");
	ImGui::SliderFloat3("t", &ballModelWorldTransform_.translate.x, -3.0f, 3.0f);

	ImGui::SliderFloat3("r", &ballModelWorldTransform_.rotation.x, -3.0f, 3.0f);

	ImGui::End();

	//画像切り替え
	sprite_->SetTexHandle(SpritemobTexHandle_);
	if (Input::PushKey(DIK_I))
	{
		TextureManager::UnUsedFilePath();
		sprite_->SetTexHandle(SpriteCLEYERATexHandle_);
	}

	
	ImGui::Begin("Light");
	ImGui::ColorPicker3("color", &pointLight_.color.x);

	ImGui::DragFloat3("pos", &pointLight_.position.x, -1.0f, 1.0f);
	ImGui::DragFloat("intensity", &pointLight_.intencity, -1.0f, 1.0f);
	ImGui::DragFloat("radious", &pointLight_.radious, -1.0f, 1.0f);
	ImGui::DragFloat("decay", &pointLight_.decay, -1.0f, 1.0f);
	ImGui::End();
	
	ImGui::Begin("LightB");
	ImGui::ColorPicker3("colorB", &pointLightB_.color.x);
	ImGui::DragFloat3("posB", &pointLightB_.position.x, -1.0f, 1.0f);
	ImGui::DragFloat("intensityB", &pointLightB_.intencity, -1.0f, 1.0f);
	ImGui::DragFloat("radiousB", &pointLightB_.radious, -1.0f, 1.0f);
	ImGui::DragFloat("decayB", &pointLightB_.decay, -1.0f, 1.0f);
	ImGui::End();

	ImGui::Begin("LightC");
	ImGui::ColorPicker3("colorC", &pointLightC_.color.x);
	ImGui::DragFloat3("posC", &pointLightC_.position.x, -1.0f, 1.0f);
	ImGui::DragFloat("intensityC", &pointLightC_.intencity, -1.0f, 1.0f);
	ImGui::DragFloat("radiousC", &pointLightC_.radious, -1.0f, 1.0f);
	ImGui::DragFloat("decayC", &pointLightC_.decay, -1.0f, 1.0f);
	ImGui::End();


	ImGui::Begin("Sun");
	ImGui::ColorPicker3("colorB", &sunLight_.color.x);
	ImGui::DragFloat3("posB", &sunLight_.position.x, -1.0f, 1.0f);
	ImGui::DragFloat("intensityB", &sunLight_.intencity, -1.0f, 1.0f);
	ImGui::DragFloat("radiousB", &sunLight_.radious, -1.0f, 1.0f);
	ImGui::DragFloat("decayB", &sunLight_.decay, -1.0f, 1.0f);
	ImGui::End();

	ImGui::Begin("particle");
	ImGui::DragFloat3("pos", &pointFireLightPosition_.x);
	ImGui::End();

	
	LightingManager::ClearList();

	fireParticle_->Update(pointFireLightPosition_);

	player_->Update();
	enemy_->Update();
	Collisions();

	LightingManager::ClearList();

	
	LightingManager::AddList(pointLightB_);
	LightingManager::AddList(pointLight_);
	LightingManager::AddList(pointLightC_);
	LightingManager::AddList(sunLight_);
	
	LightingManager::TransfarBuffers();

	ImGui::Begin("LightNum");
	ImGui::Text("%d", LightingManager::GetNowLight());
	ImGui::End();

	testSkyDomeWorldTransform_.UpdateMatrix();
	ballModelWorldTransform_.UpdateMatrix();
    modelWorldTransform_.UpdateMatrix();
	spriteWorldTransform_.UpdateMatrix();
	viewProjection.UpdateMatrix();

}

void DebugScene::Back2dSpriteDraw()
{
}

void DebugScene::Object3dDraw()
{
	player_->Draw(viewProjection);
	enemy_->Draw(viewProjection);
	//BallModel_->Draw(ballModelWorldTransform_, viewProjection);
	model_->Draw(modelWorldTransform_, viewProjection);
	testSkyDome_->Draw(testSkyDomeWorldTransform_, viewProjection);
	fireParticle_->Draw(viewProjection);
}
void DebugScene::Flont2dSpriteDraw()
{
	sprite_->Draw(spriteWorldTransform_,viewProjection);
}

void DebugScene::Collisions()
{
	/*collisionManager->ClliderClear();
	collisionManager->ClliderAABBPush(player_.get());
	collisionManager->ClliderAABBPush(enemy_.get());
	collisionManager->CheckAllCollision();*/
}




