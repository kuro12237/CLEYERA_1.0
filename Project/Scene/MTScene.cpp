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


	Quaternion rotation = QuaternionTransform::MakeQuaternionRotateAxisAngle(
		VectorTransform::Normalize({ 1.0f,0.4f,-0.2f }), 0.45f
	);

	Vector3 pointY = { 2.1f,-0.9f,1.3f };
	Matrix4x4 rotateMatrix = QuaternionTransform::MakeRotateMatrix(rotation);

	Vector3 rByQuaternion = QuaternionTransform::RotateVector(pointY, rotation);
	Vector3 rByMat = VectorTransform::TransformNormal(pointY, rotateMatrix);

	ImGui::Begin("MT_01_04");

	ImGui::Text("rotation : %0.2f %0.2f %0.2f %0.2f",rotation.x, rotation.y, rotation.z, rotation.w);
	ImGui::Text("RotateMatrix");
	

	ImGui::Text("%0.3f %0.3f %0.3f %0.3f", rotateMatrix.m[0][0], rotateMatrix.m[0][1], rotateMatrix.m[0][2], rotateMatrix.m[0][3]);
	ImGui::Text("%0.3f %0.3f %0.3f %0.3f", rotateMatrix.m[1][0], rotateMatrix.m[1][1], rotateMatrix.m[1][2], rotateMatrix.m[1][3]);
	ImGui::Text("%0.3f %0.3f %0.3f %0.3f", rotateMatrix.m[2][0], rotateMatrix.m[2][1], rotateMatrix.m[2][2], rotateMatrix.m[2][3]);
	ImGui::Text("%0.3f %0.3f %0.3f %0.3f", rotateMatrix.m[3][0], rotateMatrix.m[3][1], rotateMatrix.m[3][2], rotateMatrix.m[3][3]);

	ImGui::Text("rotateByQuaternion : %0.2f %0.2f %0.2f", rByQuaternion.x, rByQuaternion.y, rByQuaternion.z);
	ImGui::Text("rotateByMatrix : %0.2f %0.2f %0.2f", rByMat.x, rByMat.y, rByMat.z);

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
