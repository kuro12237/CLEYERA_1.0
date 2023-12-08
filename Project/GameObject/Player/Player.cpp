#include "Player.h"

void Player::Initialize()
{
	this->model_ = make_unique<Model>();
	TextureManager::UnUsedFilePath();
	//uint32_t tex = TextureManager::LoadTexture("Resources/Default/uvChecker.png");
	//this->model_->SetTexHandle(tex);
	//this->model_->CreateModel(make_unique<ModelSphereState>());

	this->playerObjPath_ = ModelManager::LoadObjectFile("DemoPlayer");
	this->model_->SetModel(playerObjPath_);
	this->model_->CreateModel(make_unique<ModelObjState>());
	this->worldTransform_.Initialize();

	SettingColliderAttributeAndMask();
}

void Player::Update()
{
	this->model_->SetColor({ 1,1,1,1 });

	if (Input::PushKey(DIK_A))
	{
		this->worldTransform_.translate.x -= 0.1f;
	}
	if (Input::PushKey(DIK_D))
	{
		this->worldTransform_.translate.x += 0.1f;
	}

	if (Input::PushKey(DIK_W))
	{
		this->worldTransform_.translate.y -= 0.1f;
	}
	if (Input::PushKey(DIK_S))
	{
		this->worldTransform_.translate.y += 0.1f;
	}

	if (Input::PushKey(DIK_R))
	{
		this->worldTransform_.translate.z -= 0.1f;
	}
	if (Input::PushKey(DIK_F))
	{
		this->worldTransform_.translate.z += 0.1f;
	}

	this->worldTransform_.UpdateMatrix();
}

void Player::Draw(ViewProjection view)
{
	this->model_->Draw(this->worldTransform_, view);
}

Vector3 Player::GetWorldPosition()
{
	Vector3 result{};
	result.x = worldTransform_.matWorld.m[3][0];
	result.y = worldTransform_.matWorld.m[3][1];
	result.z = worldTransform_.matWorld.m[3][2];

	return result;
}

void Player::OnCollision(uint32_t id)
{
	id;
	this->model_->SetColor({ 1,0,0,1 });
}


void Player::SettingColliderAttributeAndMask() {

	AABBCollider::SetCollosionAttribute(kCollisionAttributePlayer);
	AABBCollider::SetCollisionMask(kCollisionMaskPlayer);
	OBBCollider::SetCollosionAttribute(kCollisionAttributePlayer);
	OBBCollider::SetCollisionMask(kCollisionMaskPlayer);
}