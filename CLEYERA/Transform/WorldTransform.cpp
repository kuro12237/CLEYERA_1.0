#include "WorldTransform.h"

void WorldTransform::CreateBuffer()
{
	buffer_ = CreateResources::CreateBufferResource(sizeof(TransformationMatrix));

}

void WorldTransform::Map()
{
	buffer_->Map(0, nullptr, reinterpret_cast<void**>(&BufferMatrix_));
}

void WorldTransform::UnMap()
{
	buffer_->Unmap(0,nullptr);
}

void WorldTransform::Initialize()
{
	CreateBuffer();
	matWorld = MatrixTransform::Identity();
	TransfarMatrix();
}

void WorldTransform::SRTSetting(Vector3 s, Vector3 r, Vector3 t)
{
	scale = s;
	rotation = r;
	translate = t;
	//UpdateMatrix();
}

void WorldTransform::UpdateMatrix(ViewProjection viewProjection, Projection Flag)
{
	matWorld = MatrixTransform::AffineMatrix(scale, rotation, translate);

	if (parent) {
		matWorld = MatrixTransform::Multiply(matWorld, parent->matWorld);
	}

	viewProjection;
	//ViewProjectionを定数にするまで
	if (Flag == PerspectiveFov)
	{
		//matWorld = MatrixTransform::Multiply(matWorld, MatrixTransform::Multiply(viewProjection.matView_, viewProjection.matProjection_));
	}
	if (Flag == OrthographicMatrix)
	{
		Matrix4x4 viewMatrix = MatrixTransform::Identity();
		Matrix4x4 testOrthographicMatrix = MatrixTransform::OrthographicMatrix(
			0, 0, float(WinApp::GetkCilientWidth()), float(WinApp::GetkCilientHeight()), 0.0f, 100.0f
		);

		matWorld = MatrixTransform::Multiply(matWorld, MatrixTransform::Multiply(viewMatrix, testOrthographicMatrix));
	}


	
	TransfarMatrix();
}

void WorldTransform::TransfarMatrix(ComPtr<ID3D12Resource>& wvpResource, ViewProjection viewProjection, Projection Flag )
{
	TransformationMatrix* wvp = {};
	wvpResource->Map(0, nullptr, reinterpret_cast<void**>(&wvp));
	if (Flag == PerspectiveFov)
	{
		matWorld = MatrixTransform::Multiply(matWorld, MatrixTransform::Multiply(viewProjection.matView_, viewProjection.matProjection_));
	}
	if (Flag==OrthographicMatrix)
	{
		Matrix4x4 viewMatrix = MatrixTransform::Identity();
		Matrix4x4 OrthographicMatrix = MatrixTransform::OrthographicMatrix(
			0, 0, float(WinApp::GetkCilientWidth()), float(WinApp::GetkCilientHeight()), 0.0f, 100.0f
		);

		matWorld =MatrixTransform::Multiply(matWorld,MatrixTransform::Multiply(viewMatrix,OrthographicMatrix));
	}
	wvp->WVP = matWorld;
	wvp->world = MatrixTransform::Identity();
	
}

void WorldTransform::TransfarMatrix()
{
	Map();
	BufferMatrix_->WVP = matWorld;
	BufferMatrix_->world = MatrixTransform::Identity();
	UnMap();
}
