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
	//rotateMatrix_ = Quaternion::MakeRotateAxisAngle(axis_, angle);
	//axis_ = VectorTransform::Normalize(axis_);

	Vector3 flom0 = VectorTransform::Normalize({ 1.0f,0.7f,0.5f });
	Vector3 to0 = { -flom0.x,-flom0.y,-flom0.z };

	Vector3 flom1 = VectorTransform::Normalize({ -0.6f,0.9f,0.2f });
	Vector3 to1 = VectorTransform::Normalize({0.4f, 0.7f, -0.5f});

	Matrix4x4 rotateMatrix0_ = Quaternion::DirectionToDirection(VectorTransform::Normalize({ 1.0f,0.0f,0.0f }), VectorTransform::Normalize({-1.0f,0.0f,0.0f}));
	Matrix4x4 rotateMatrix1_ = Quaternion::DirectionToDirection(flom0,to0);
	rotateMatrix_ = Quaternion::DirectionToDirection(flom1,to1 );

	ImGui::Begin("MT_01_02");
	
	ImGui::Text("rotate00");
	ImGui::Text("%0.3f,%0.3f,%0.3f,%0.3f", rotateMatrix0_.m[0][0], rotateMatrix0_.m[1][0], rotateMatrix0_.m[2][0], rotateMatrix0_.m[3][0]);
	ImGui::Text("%0.3f,%0.3f,%0.3f,%0.3f", rotateMatrix0_.m[0][1], rotateMatrix0_.m[1][1], rotateMatrix0_.m[2][1], rotateMatrix0_.m[3][1]);
	ImGui::Text("%0.3f,%0.3f,%0.3f,%0.3f", rotateMatrix0_.m[0][2], rotateMatrix0_.m[1][2], rotateMatrix0_.m[2][2], rotateMatrix0_.m[3][2]);
	ImGui::Text("%0.3f,%0.3f,%0.3f,%0.3f", rotateMatrix0_.m[0][3], rotateMatrix0_.m[1][3], rotateMatrix0_.m[2][3], rotateMatrix0_.m[3][3]);


	ImGui::Text("rotate01");
	ImGui::Text("%0.3f,%0.3f,%0.3f,%0.3f", rotateMatrix1_.m[0][0], rotateMatrix1_.m[1][0], rotateMatrix1_.m[2][0], rotateMatrix1_.m[3][0]);
	ImGui::Text("%0.3f,%0.3f,%0.3f,%0.3f", rotateMatrix1_.m[0][1], rotateMatrix1_.m[1][1], rotateMatrix1_.m[2][1], rotateMatrix1_.m[3][1]);
	ImGui::Text("%0.3f,%0.3f,%0.3f,%0.3f", rotateMatrix1_.m[0][2], rotateMatrix1_.m[1][2], rotateMatrix1_.m[2][2], rotateMatrix1_.m[3][2]);
	ImGui::Text("%0.3f,%0.3f,%0.3f,%0.3f", rotateMatrix1_.m[0][3], rotateMatrix1_.m[1][3], rotateMatrix1_.m[2][3], rotateMatrix1_.m[3][3]);

	ImGui::Text("rotate02");
	ImGui::Text("%0.3f,%0.3f,%0.3f,%0.3f", rotateMatrix_.m[0][0], rotateMatrix_.m[1][0], rotateMatrix_.m[2][0], rotateMatrix_.m[3][0] );
	ImGui::Text("%0.3f,%0.3f,%0.3f,%0.3f", rotateMatrix_.m[0][1], rotateMatrix_.m[1][1], rotateMatrix_.m[2][1], rotateMatrix_.m[3][1]);
	ImGui::Text("%0.3f,%0.3f,%0.3f,%0.3f", rotateMatrix_.m[0][2], rotateMatrix_.m[1][2], rotateMatrix_.m[2][2], rotateMatrix_.m[3][2]);
	ImGui::Text("%0.3f,%0.3f,%0.3f,%0.3f", rotateMatrix_.m[0][3], rotateMatrix_.m[1][3], rotateMatrix_.m[2][3], rotateMatrix_.m[3][3]);

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
	model_->Draw(worldTransform_, viewProjection_);
}

void MTScene::Flont2dSpriteDraw()
{
}
