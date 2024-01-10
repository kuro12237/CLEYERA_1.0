#include "MTScene.h"

void MTScene::Initialize()
{
	model_ = make_unique<Model>();
	model_;
	worldTransform_.Initialize();

	viewProjection_.Initialize({ 0,0,0.0f }, { 0.0f,0.0f,-5.0f });
	viewProjection_.UpdateMatrix();
}

void MTScene::Update(GameManager* Scene)
{
	Scene;


	
	Vector3 rotateV0 = { 0.71f, 0.71f, 0.0f };
	Vector3 rotateV1 = { 0.71f, 0.0f, 0.71f };

	rotateV0 = VectorTransform::Normalize(rotateV0);
	rotateV1 = VectorTransform::Normalize(rotateV1);


    Quaternion rotate0 = QuaternionTransform::MakeQuaternionRotateAxisAngle(rotateV0, 0.3f);
	Quaternion rotate1 = QuaternionTransform::MakeQuaternionRotateAxisAngle(rotateV1,3.141592f);

	rotate0, rotate1;

	ImGui::Begin("MT_01_05");

	Quaternion SR0 = QuaternionTransform::Slerp(rotate0, rotate1, 0.0f);

	Quaternion SR1 = QuaternionTransform::Slerp(rotate0, rotate1, 0.3f);

	Quaternion SR2 = QuaternionTransform::Slerp(rotate0, rotate1, 0.5f);

	Quaternion SR3 = QuaternionTransform::Slerp(rotate0, rotate1, 0.7f);

	Quaternion SR4 = QuaternionTransform::Slerp(rotate0, rotate1, 1.0f);


	ImGui::Text("%0.2f %0.2f %0.2f %0.2f", SR0.x, SR0.y, SR0.z, SR0.w);
	ImGui::Text("%0.2f %0.2f %0.2f %0.2f", SR1.x, SR1.y, SR1.z, SR1.w);
	ImGui::Text("%0.2f %0.2f %0.2f %0.2f", SR2.x, SR2.y, SR2.z, SR2.w);
	ImGui::Text("%0.2f %0.2f %0.2f %0.2f", SR3.x, SR3.y, SR3.z, SR3.w);
	ImGui::Text("%0.2f %0.2f %0.2f %0.2f", SR4.x, SR4.y, SR4.z, SR4.w);

	ImGui::End();

	

	Matrix4x4 sMat = MatrixTransform::ScaleMatrix(worldTransform_.scale);
	
	Matrix4x4 tMat = MatrixTransform::TranslateMatrix(worldTransform_.translate);
	
	Matrix4x4 matWorld = MatrixTransform::Multiply(sMat, MatrixTransform::Multiply(rotateMatrix_, tMat));
	
	worldTransform_.matWorld = MatrixTransform::Multiply(matWorld, MatrixTransform::Multiply(viewProjection_.matView_, viewProjection_.matProjection_));
	//worldTransform_.UpdateMatrix();

	worldTransform_.TransfarMatrix();
	viewProjection_.UpdateMatrix();
}

void MTScene::Back2dSpriteDraw()
{
}

void MTScene::Object3dDraw()
{
	//model_->Draw(worldTransform_, viewProjection_);
}

void MTScene::Flont2dSpriteDraw()
{
}
