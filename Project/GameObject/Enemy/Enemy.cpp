#include "Enemy.h"

void Enemy::Initialize()
{
	this->model_ = make_unique<Model>();
	this->EnemyObjPath_ = ModelManager::LoadObjectFile("Enemy");
	this->model_->SetModel(EnemyObjPath_);
	this->model_->CreateModel(make_unique<ModelObjState>());
	this->worldTransform_.Initialize();
	this->size_ = {
		.x = 20.0f * worldTransform_.scale.x,
		.y = 2.0f * worldTransform_.scale.y,
		.z = 20.0f * worldTransform_.scale.z
	};

	SettingColliderAttributeAndMask();

}


void Enemy::Update()
{
	this->worldTransform_.UpdateMatrix();

	this->size_ = {
		.x = 20.0f * worldTransform_.scale.x,
		.y = 2.0f * worldTransform_.scale.y,
		.z = 20.0f * worldTransform_.scale.z
	};


#ifdef _DEBUG

	ImGui::Begin("Enemy");
	ImGui::Text("WorldTransform");
	ImGui::DragFloat3("Scale", &this->worldTransform_.scale.x, 0.01f, 0.0f, 10.0f);
	ImGui::DragFloat3("Rotate", &this->worldTransform_.rotation.x, 0.01f);
	ImGui::DragFloat3("Translate", &this->worldTransform_.translate.x, 0.1f);
	ImGui::Text("Size");
	ImGui::DragFloat3("Size", &this->size_.x, 0.01f);
	ImGui::End();

#endif // _DEBUG
}


void Enemy::Draw(ViewProjection view)
{
	this->model_->Draw(this->worldTransform_, view);
}


Vector3 Enemy::GetWorldPosition()
{
	Vector3 result{};
	result.x = worldTransform_.matWorld.m[3][0];
	result.y = worldTransform_.matWorld.m[3][1];
	result.z = worldTransform_.matWorld.m[3][2];

	return result;

}


void Enemy::OnCollision(uint32_t id)
{
	id;
}


void Enemy::SettingColliderAttributeAndMask() {

	AABBCollider::SetCollosionAttribute(kCollisionAttributeEnemy);
	AABBCollider::SetCollisionMask(kCollisionMaskEnemy);
	OBBCollider::SetCollosionAttribute(kCollisionAttributeEnemy);
	OBBCollider::SetCollisionMask(kCollisionMaskEnemy);
}