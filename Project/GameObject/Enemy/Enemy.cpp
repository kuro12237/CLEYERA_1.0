#include "Enemy.h"

void Enemy::Initialize()
{
	this->model_ = make_unique<Model>();
	TextureManager::UnUsedFilePath();
	uint32_t tex = TextureManager::LoadTexture("Resources/Default/uvChecker.png");
	this->model_->SetTexHandle(tex);
	this->model_->CreateModel(make_unique<ModelSphereState>());
	this->worldTransform_.Initialize();

	SettingColliderAttributeAndMask();
}

void Enemy::Update()
{
	this->worldTransform_.UpdateMatrix();
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