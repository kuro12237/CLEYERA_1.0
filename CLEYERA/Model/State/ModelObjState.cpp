#include "ModelObjState.h"

void ModelObjState::Initialize(Model* state)
{
	ModelData_ = LoadFile(state,state->GetObjDirectoryPath());
	resource_.Vertex = CreateResources::CreateBufferResource(sizeof(VertexData) * ModelData_.vertices.size());
	resource_.Material = CreateResources::CreateBufferResource(sizeof(Material));

	resource_.BufferView = CreateResources::VertexCreateBufferView(sizeof(VertexData) * ModelData_.vertices.size(), resource_.Vertex,int( ModelData_.vertices.size()));
	if (state->GetUseLight() != NONE)
	{
		resource_.Light = CreateResources::CreateBufferResource(sizeof(LightData));
	}
}

void ModelObjState::Draw(Model* state, WorldTransform worldTransform, ViewProjection viewprojection)
{
	VertexData* vertexData = nullptr;
	Material* materialData = nullptr;

	resource_.Vertex->Map(0, nullptr, reinterpret_cast<void**>(&vertexData));
	resource_.Material->Map(0, nullptr, reinterpret_cast<void**>(&materialData));

	memcpy(vertexData, ModelData_.vertices.data(), sizeof(VertexData) * ModelData_.vertices.size());

	materialData->color = state->GetColor();
	materialData->uvTransform = MatrixTransform::AffineMatrix(state->GetuvScale(), state->GetuvRotate(), state->GetuvTranslate());
	if (state->GetUseLight() != NONE)
	{
		LightData* lightData = nullptr;
		resource_.Light->Map(0, nullptr, reinterpret_cast<void**>(&lightData));

		lightData->color = { 1.0f,1.0f,1.0f,1.0f };
		lightData->direction = { 0.0f,-1.0f,0.0f };
		lightData->intensity = 1.0f;

	}

	Commands commands = DirectXCommon::GetInstance()->GetCommands();
	SPSOProperty PSO = GraphicsPipelineManager::GetInstance()->GetPso().Sprite3d.none;
	if (state->GetUseLight() == HARF_LAMBERT)
	{
		PSO = GraphicsPipelineManager::GetInstance()->GetPso().Herf_Lambert;
	}

	commands.m_pList->SetGraphicsRootSignature(PSO.rootSignature.Get());
	commands.m_pList->SetPipelineState(PSO.GraphicsPipelineState.Get());

	commands.m_pList->IASetVertexBuffers(0, 1, &resource_.BufferView);

	commands.m_pList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	commands.m_pList->SetGraphicsRootConstantBufferView(0, resource_.Material->GetGPUVirtualAddress());
	commands.m_pList->SetGraphicsRootConstantBufferView(1, worldTransform.buffer_->GetGPUVirtualAddress());
	commands.m_pList->SetGraphicsRootConstantBufferView(2, viewprojection.buffer_->GetGPUVirtualAddress());
	DescriptorManager::rootParamerterCommand(3, state->GetTexHandle());
	if (state->GetUseLight() != NONE)
	{
		commands.m_pList->SetGraphicsRootConstantBufferView(4, resource_.Light->GetGPUVirtualAddress());
	}

	commands.m_pList->DrawInstanced(UINT(ModelData_.vertices.size()), 1, 0, 0);

}


SModelData ModelObjState::LoadFile(Model *state,const string& directoryPath)
{
	SModelData modelData = {};

	Assimp::Importer importer;
	string file("Resources/" + directoryPath + "/" + directoryPath + ".obj");
	const aiScene* scene = importer.ReadFile(file.c_str(), aiProcess_FlipWindingOrder | aiProcess_FlipUVs);
	assert(scene->HasMeshes());

	//mesh解析
	for (uint32_t meshIndex = 0; meshIndex < scene->mNumMeshes; ++meshIndex)
	{
		aiMesh* mesh = scene->mMeshes[meshIndex];
		assert(mesh->HasNormals());
		assert(mesh->HasTextureCoords(0));
		//Fenceの解析
		for (uint32_t faceIndex = 0; faceIndex < mesh->mNumFaces; ++faceIndex)
		{
			aiFace& face = mesh->mFaces[faceIndex];
			assert(face.mNumIndices == 3);
			//Vertex解析
			for (uint32_t element = 0; element < face.mNumIndices; ++element)
			{
				uint32_t vertexIndex = face.mIndices[element];
				aiVector3D& position = mesh->mVertices[vertexIndex];
				aiVector3D& normal = mesh->mNormals[vertexIndex];
				aiVector3D& texcoord = mesh->mTextureCoords[0][vertexIndex];
				VertexData vertex;
				vertex.position = { position.x,position.y,position.z,1.0f };
				vertex.normal = { normal.x,normal.y,normal.z };
				vertex.texcoord = { texcoord.x,texcoord.y };
				//座標反転
				vertex.position.x *= -1.0f;
				vertex.normal.x *= -1.0f;
				modelData.vertices.push_back(vertex);
			}
		}
	}
	//materialの解析
	for (uint32_t materialIndex = 0; materialIndex < scene->mNumMaterials; materialIndex++)
	{
		aiMaterial* material = scene->mMaterials[materialIndex];
		if (material->GetTextureCount(aiTextureType_DIFFUSE) != 0)
		{
			aiString texFilePath;
			material->GetTexture(aiTextureType_DIFFUSE, 0, &texFilePath);
			modelData.material.textureFilePath = "Resources/" + directoryPath + "/" + texFilePath.C_Str();
		}
	}
	TextureManager::UnUsedFilePath();
	uint32_t texHandle = TextureManager::LoadTexture(modelData.material.textureFilePath);
	

	state->SetTexHandle(texHandle);
	
	return modelData;
}

MaterialData ModelObjState::LoadMaterialTemplateFile(const string& directoryPath, const string& filename)
{
	MaterialData materialData;
	string line;
	ifstream file("Resources/" + directoryPath + "/" + filename);
	assert(file.is_open());
	while (getline(file, line))
	{
		string identifier;
		istringstream s(line);
		s >> identifier;

		if (identifier == "map_Kd")
		{
			string texfilename;
			s >> texfilename;
			materialData.textureFilePath = "Resources/" + directoryPath + "/" + texfilename;

		}
	}

	return materialData;
}
