#include"Harf_LambertLightObject.hlsli"


struct Material
{
	float32_t4 color;
	float32_t4x4 uv;
	float32_t shininess;
};
struct DirectionalLight {
	float32_t4 color;
	float32_t3 direction;
	
	float intensity;

};

struct PointLight
{
	float32_t4 color;
	float32_t3 position;
	float intensity;
	float redious;
	float decay;
};


ConstantBuffer<Material>gMaterial :register(b0);

ConstantBuffer<DirectionalLight> gDirectionalLight : register(b1);
ConstantBuffer<TransformationViewMatrix> gTransformationViewMatrix : register(b2);
ConstantBuffer<PointLight> gPointLight : register(b3);

Texture2D<float32_t4>gTexture : register(t0);
SamplerState gSampler : register(s0);

struct PixelShaderOutput {

	float32_t4 color : SV_TARGET0;
};

PixelShaderOutput main(VertexShaderOutput input) {

	PixelShaderOutput output;

	float32_t4 textureColor = gTexture.Sample(gSampler, input.texcoord);

	float32_t distance = length(gPointLight.position - input.worldPosition);
	float32_t factor = 1.0f / (distance * distance);

	float NdotL = dot(normalize(input.normal), -normalize(gDirectionalLight.direction));
	float cos = pow(NdotL * 0.5f + 0.5f,2.0f);
	//拡散
	float32_t3 diffuse = gMaterial.color.rgb * textureColor.rgb * gDirectionalLight.color.rgb * cos * gDirectionalLight.intensity * factor;

	//鏡面
	float32_t3 toEye = normalize(gTransformationViewMatrix.CameraPosition - input.worldPosition);

	float32_t3 reflectLight = reflect(normalize(gDirectionalLight.direction), normalize(input.normal));
	float RdoE = dot(reflectLight, toEye);

	
	float32_t3 halfVector = normalize(-gDirectionalLight.direction + toEye);
	float NDotH = dot(normalize(input.normal), halfVector);

	float specularPow = pow(saturate(NDotH), gMaterial.shininess);
	float32_t3 specular = gDirectionalLight.color.rgb * gDirectionalLight.intensity * factor * specularPow * float32_t3(1.0f, 1.0f, 1.0f);
	

	//点光源

	float32_t3 pLightDirection = normalize(input.worldPosition - gPointLight.position);
	float32_t3 pRefrectLight = reflect(pLightDirection, normalize(input.normal));
	float32_t3 pHalfVector = normalize(-pLightDirection + toEye);


	float pNdotL = dot(normalize(input.normal), -normalize(pLightDirection));
	float pCos = pow(NdotL * 0.5f + 0.5f, 2.0f);
	float pNdotH = dot(normalize(input.normal), pHalfVector);
	//拡散
	float32_t3 pDiffuse = gMaterial.color.rgb * textureColor.rgb * gPointLight.color.rgb * pCos * gPointLight.intensity * factor;
	//鏡面
	float pSpecularPow = pow(saturate(pNdotH), gMaterial.shininess);
	float32_t3 pSpecular = gPointLight.color.rgb * gPointLight.intensity * factor * pSpecularPow * float32_t3(1.0f, 1.0f, 1.0f);


	output.color.rgb = diffuse + specular + pDiffuse + pSpecular;
	output.color.a = gMaterial.color.a * textureColor.a;

	//output.color = gMaterial.color * textureColor*gDirectionalLight.color* cos* gDirectionalLight.intensity;
	// gMaterial.color * textureColor;

	return output;
}