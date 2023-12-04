#pragma once
#include"Model.h"

class Player
{
public:
	Player() {};
	~Player() {};

	void Initialize();

	void Update();

	void Draw(ViewProjection viewProjection);

	void MoveRight();

	void MoveLeft();

private:

	unique_ptr<Model>model_ = nullptr;
	WorldTransform worldTransform_;
	float speed_ = 0.1f;

	uint32_t texHandle = 0;
};
