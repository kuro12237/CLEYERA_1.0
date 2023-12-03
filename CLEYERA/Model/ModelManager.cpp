#include "ModelManager.h"

ModelManager* ModelManager::GetInstance()
{
	static ModelManager instance;
	return &instance;
}

void ModelManager::Initialize()
{

}

void ModelManager::Finalize()
{
	ModelManager::GetInstance()->objModelDatas_.clear();
}

uint32_t ModelManager::LoadObjectFile(string directoryPath)
{
	if (ChackLoadObj(directoryPath))
	{
		//始めてだったら加算
		ModelManager::GetInstance()->objHandle_++;

		uint32_t modelHandle = ModelManager::GetInstance()->objHandle_;
		SModelData modelData = {};

		//Assimp::Importer importer;
		//string file("Resources/" + directoryPath + "/" + directoryPath + ".obj");
		//const aiScene* scene = importer.ReadFile(file.c_str(), aiProcess_FlipWindingOrder | aiProcess_FlipUVs);
		//assert(scene->HasMeshes());

		////mesh解析
		//for (uint32_t meshIndex = 0; meshIndex < scene->mNumMeshes; ++meshIndex)
		//{
		//	aiMesh* mesh = scene->mMeshes[meshIndex];
		//	assert(mesh->HasNormals());
		//	assert(mesh->HasTextureCoords(0));
		//	//Fenceの解析
		//	for (uint32_t faceIndex = 0; faceIndex < mesh->mNumFaces; ++faceIndex)
		//	{
		//		aiFace& face = mesh->mFaces[faceIndex];
		//		assert(face.mNumIndices == 3);
		//		//Vertex解析
		//		for (uint32_t element = 0; element < face.mNumIndices; ++element)
		//		{
		//			uint32_t vertexIndex = face.mIndices[element];
		//			aiVector3D& position = mesh->mVertices[vertexIndex];
		//			aiVector3D& normal = mesh->mNormals[vertexIndex];
		//			aiVector3D& texcoord = mesh->mTextureCoords[0][vertexIndex];
		//			VertexData vertex;
		//			vertex.position = { position.x,position.y,position.z,1.0f };
		//			vertex.normal = { normal.x,normal.y,normal.z };
		//			vertex.texcoord = { texcoord.x,texcoord.y };
		//			//座標反転
		//			vertex.position.x *= -1.0f;
		//			vertex.normal.x *= -1.0f;
		//			modelData.vertices.push_back(vertex);
		//		}
		//	}
		//}
		////materialの解析
		//for (uint32_t materialIndex = 0; materialIndex < scene->mNumMaterials; materialIndex++)
		//{
		//	aiMaterial* material = scene->mMaterials[materialIndex];
		//	if (material->GetTextureCount(aiTextureType_DIFFUSE) != 0)
		//	{
		//		aiString texFilePath;
		//		material->GetTexture(aiTextureType_DIFFUSE, 0, &texFilePath);
		//		modelData.material.textureFilePath = "Resources/" + directoryPath + "/" + texFilePath.C_Str();
		//	}
		//}

		vector<Vector4> positions;
		vector<Vector3> normals;
		vector<Vector2> texcoords;
		string line;
		ifstream file("Resources/" + directoryPath + "/" + directoryPath + ".obj");
		assert(file.is_open());

		while (getline(file, line))
		{
			string identifier;
			istringstream s(line);
			s >> identifier;

			if (identifier == "v")
			{   //v���_�ʒu
				Vector4 position = {};
				s >> position.x >> position.y >> position.z;

				position.z *= -1.0f;
				position.w = 1.0f;
				positions.push_back(position);
			}
			else if (identifier == "vt")
			{	//vt���_�e�N�X�`���̍��W
				Vector2 texcoord = {};
				s >> texcoord.x >> texcoord.y;
				texcoord.y *= -1.0f;

				texcoords.push_back(texcoord);
			}
			else if (identifier == "vn")
			{   //vn���_�@��
				Vector3 normal = {};

				s >> normal.x >> normal.y >> normal.z;
				normal.z *= -1.0f;
				normals.push_back(normal);
			}
			else if (identifier == "f") {
				VertexData triangle[3] = {};
				for (int32_t faceVertex = 0; faceVertex < 3; ++faceVertex) {
					string vertexDefinition = {};
					s >> vertexDefinition;
					//�������Index��Get
					istringstream v(vertexDefinition);
					uint32_t elementIndices[3] = {};
					for (int32_t element = 0; element < 3; ++element) {
						string index;
						getline(v, index, '/');
						elementIndices[element] = stoi(index);
					}

					Vector4 position = positions[elementIndices[0] - 1];
					Vector2 texcoord = texcoords[elementIndices[1] - 1];
					Vector3 normal = normals[elementIndices[2] - 1];
					triangle[faceVertex] = { position,texcoord,normal };
				}
				//���_��t���œo�^���邱�ƂŁA��菇��t�ɂ���
				modelData.vertices.push_back(triangle[2]);
				modelData.vertices.push_back(triangle[1]);
				modelData.vertices.push_back(triangle[0]);
			}
			else if (identifier == "mtllib") {
				//tex
				string materialFilename;
				s >> materialFilename;
				modelData.material = LoadMaterialTemplateFile(directoryPath, materialFilename);
			}
		}
		TextureManager::UnUsedFilePath();
		uint32_t texHandle = TextureManager::LoadTexture(modelData.material.textureFilePath);
		modelData.material.handle = texHandle;

		ModelManager::GetInstance()->objModelDatas_[directoryPath] = make_unique<ModelObjData>(modelData, modelHandle);

		return modelHandle;
	}

	return ModelManager::GetInstance()->objModelDatas_[directoryPath]->GetIndex();
}

SModelData ModelManager::GetObjData(uint32_t index)
{
	SModelData data{};
	for (const auto& [key, s] : ModelManager::GetInstance()->objModelDatas_)
	{
		key;
		if (s.get()->GetIndex() == index)
		{
			data = s.get()->GetData();
			return data;
			break;
		}
	}

	return data;
}

bool ModelManager::ChackLoadObj(string filePath)
{
	if (ModelManager::GetInstance()->objModelDatas_.find(filePath) == ModelManager::GetInstance()->objModelDatas_.end())
	{
		return true;
	}
	return false;
}

MaterialData ModelManager::LoadMaterialTemplateFile(const string& directoryPath, const string& filename)
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