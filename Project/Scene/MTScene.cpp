#include "MTScene.h"

void MTScene::Initialize()
{
	model_ = make_unique<Model>();
	model_->CreateFromObj("axis");
	worldTransform_.Initialize();

	viewProjection_.Initialize({ 0,0,0.0f }, { 0.0f,0.0f,-5.0f });
	viewProjection_.UpdateMatrix();
}

void MTScene::Update(GameManager* Scene)
{
	Scene;
	rotateMatrix_ = Quaternion::MakeRotateAxisAngle(axis_, angle);
	axis_ = VectorTransform::Normalize(axis_);


	ImGui::Begin("MT_01_01");
	ImGui::SliderFloat3("x::,y::,z::", &axis_.x,0.0f,1.0f);

	ImGui::SliderFloat("angle::", &angle,0.0f,4.0f);
	ImGui::Text("%0.3f,%0.3f,%0.3f,%0.3f", rotateMatrix_.m[0][0], rotateMatrix_.m[1][0], rotateMatrix_.m[2][0], rotateMatrix_.m[3][0] );
	ImGui::Text("%0.3f,%0.3f,%0.3f,%0.3f", rotateMatrix_.m[0][1], rotateMatrix_.m[1][1], rotateMatrix_.m[2][1], rotateMatrix_.m[3][1]);
	ImGui::Text("%0.3f,%0.3f,%0.3f,%0.3f", rotateMatrix_.m[0][2], rotateMatrix_.m[1][2], rotateMatrix_.m[2][2], rotateMatrix_.m[3][2]);
	ImGui::Text("%0.3f,%0.3f,%0.3f,%0.3f", rotateMatrix_.m[0][3], rotateMatrix_.m[1][3], rotateMatrix_.m[2][3], rotateMatrix_.m[3][3]);



	ImGui::End();

	

	Matrix4x4 sMat = MatrixTransform::ScaleMatrix(worldTransform_.scale);
	
	Matrix4x4 tMat = MatrixTransform::TranslateMatrix(worldTransform_.translate);
	
	Matrix4x4 matWorld = MatrixTransform::Multiply(sMat, MatrixTransform::Multiply(rotateMatrix_, tMat));
	
	worldTransform_.matWorld = MatrixTransform::Multiply(matWorld, MatrixTransform::Multiply(viewProjection_.matView_, viewProjection_.matProjection_));

	viewProjection_.UpdateMatrix();
}

void MTScene::Back2dSpriteDraw()
{
}

void MTScene::Object3dDraw()
{
	model_->Draw(worldTransform_, viewProjection_);
}

void MTScene::Flont2dSpriteDraw()
{
}
