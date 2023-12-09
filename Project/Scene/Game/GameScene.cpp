#include "GameScene.h"



GameScene::~GameScene() {}



void GameScene::Initialize() {

	// Camera
	viewProjection.Initialize({ 0,0,0.0f }, { 0.0f,2.0f,-45.0f });

	// Player
	player_ = make_unique<Player>();
	player_->Initialize();


	// Enemy
	enemy_ = make_unique<Enemy>();
	enemy_->Initialize();


	// CollisionManager
	collisionManager_ = make_unique<CollisionManager>();

}



void GameScene::Update(GameManager* Scene) {

	// Camera
	viewProjection.UpdateMatrix();

	// Player
	player_->Update();

	// Enemy
	enemy_->Update();

	// Collision
	CheckAllCollision();

#ifdef _DEBUG

	ImGui::Begin("DemoScene");
	ImGui::End();

	ImGui::Begin("MainCamera");
	ImGui::DragFloat3("trans", &viewProjection.translation_.x, -0.2f, 0.2f);
	ImGui::DragFloat3("rotate", &viewProjection.rotation_.x, -0.1f, 0.1f);
	ImGui::End();

#endif // _DEBUG

	Scene;
}



void GameScene::Back2dSpriteDraw() {


}



void GameScene::Object3dDraw() {

	// Player
	player_->Draw(viewProjection);

	// Enemy
	enemy_->Draw(viewProjection);

}



void GameScene::Flont2dSpriteDraw() {



}




void GameScene::CheckAllCollision() {

	// �o�^���ꂽ�R���C�_�[���X�g���N���A����
	collisionManager_->ClliderClear();

	// �R���C�_�[�����X�g�ɓo�^����
	collisionManager_->ColliderAABBPushBack(player_.get());
	collisionManager_->ColliderAABBPushBack(enemy_.get());
	collisionManager_->ColliderOBBPushBack(player_.get());
	collisionManager_->ColliderOBBPushBack(enemy_.get());

	// ���ׂẴR���C�_�[�ɑ΂��ďՓ˂����o
	collisionManager_->CheckAllCollision();
}