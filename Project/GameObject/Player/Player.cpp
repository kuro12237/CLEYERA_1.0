#include "Player.h"

void Player::Initialize()
{
	this->model_ = make_unique<Model>();
	this->model_->UseLight(HARF_LAMBERT);
	this->model_->CreateModel(new ModelSphereState);
	this->worldTransform_.Initialize();
	TextureManager::UnUsedFilePath();
	this->texHandle = TextureManager::LoadTexture("Resources/Default/uvChecker.png");
	this->model_->SetTexHandle(this->texHandle);
}

void Player::Update()
{
	this->worldTransform_.UpdateMatrix();
}

void Player::Draw(ViewProjection viewProjection)
{
	this->model_->Draw(this->worldTransform_, viewProjection);
}

void Player::MoveRight()
{
	this->worldTransform_.translate.x += this->speed_;
}

void Player::MoveLeft()
{
	this->worldTransform_.translate.x -= this->speed_;
}
