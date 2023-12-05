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
ConstantBuffer<Material>gMaterial :register(b0);

ConstantBuffer<DirectionalLight> gDirectionalLight : register(b1);
ConstantBuffer<TransformationViewMatrix> gTransformationViewMatrix : register(b2);


Texture2D<float32_t4>gTexture : register(t0);
SamplerState gSampler : register(s0);

struct PixelShaderOutput {

	float32_t4 color : SV_TARGET0;
};

PixelShaderOutput main(VertexShaderOutput input) {

	PixelShaderOutput output;

	float32_t4 textureColor = gTexture.Sample(gSampler, input.texcoord);

	float NdotL = dot(normalize(input.normal), -normalize(gDirectionalLight.direction));
	float cos = pow(NdotL * 0.5f + 0.5f,2.0f);
	//拡散
	float32_t3 diffuse = gMaterial.color.rgb * textureColor.rgb * gDirectionalLight.color.rgb * cos * gDirectionalLight.intensity;

	//鏡面
	float32_t3 toEye = normalize(gTransformationViewMatrix.CameraPosition - input.worldPosition);

	float32_t3 reflectLight = reflect(normalize(gDirectionalLight.direction), normalize(input.normal));
	float RdoE = dot(reflectLight, toEye);

	
	float32_t3 halfVector = normalize(-gDirectionalLight.direction + toEye);
	float NDotH = dot(normalize(input.normal), halfVector);

	float specularPow = pow(saturate(NDotH), gMaterial.shininess);

	
	float32_t3 specular = gDirectionalLight.color.rgb * gDirectionalLight.intensity * specularPow * float32_t3(1.0f, 1.0f, 1.0f);
	

	output.color.rgb = diffuse + specular;
	output.color.a = gMaterial.color.a * textureColor.a;

	//output.color = gMaterial.color * textureColor*gDirectionalLight.color* cos* gDirectionalLight.intensity;
	// gMaterial.color * textureColor;

	return output;
}