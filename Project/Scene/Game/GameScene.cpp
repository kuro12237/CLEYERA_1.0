#include "GameScene.h"



GameScene::~GameScene() {


	//// Camera
	//viewProjection.Initialize({ 0,0,0.0f }, { 0.0f,2.0f,-12.0f });

	//// Player
	//player_ = make_unique<Player>();
	//player_->Initialize();


	//// Enemy
	//enemy_ = make_unique<Enemy>();
	//enemy_->Initialize();


	//// CollisionManager
	//collisionManager = make_unique<CollisionManager>();

}



void GameScene::Initialize() {



}



void GameScene::Update(GameManager* Scene) {

	// Camera
	viewProjection.UpdateMatrix();



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



}



void GameScene::Flont2dSpriteDraw() {



}