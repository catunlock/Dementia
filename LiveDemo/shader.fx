#include "LightHelper.fx"
//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------
Texture2D txDiffuse : register( t0 );

SamplerState samLinear : register( s0 );

cbuffer ConstantBuffer : register( b0 )
{
	matrix World;
	matrix View;
	matrix Projection;
	DirectionalLight gDirLight;
	PointLight gPointLight;
	SpotLight gSpotLight;
	Material gMaterial;
	float3 gEyePosW;
	float pad;
//	float4 vLightDir[2];
//	float4 vLightColor[2];
//	float4 vOutputColor;
};


//--------------------------------------------------------------------------------------
struct PS_INPUT
{
    float4 PosH : SV_POSITION;
	float4 PosW : POSITION;
    float3 normal : COLOR0;
	float3 normalW : NORMALIW;
	float3 tanU : TANGENTU0;
	float2 texC : TEXCOORD0;
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
PS_INPUT VS( float3 Pos : POSITION, float3 normal : COLOR, float3 tanU : TANGENTU, float2 texC : TEXCOORD)
{
    PS_INPUT output = (PS_INPUT)0;
    
	output.PosH = mul( float4(Pos, 1.0f), World );
	output.PosW = output.PosH;
    output.PosH = mul( output.PosH, View );
    output.PosH = mul( output.PosH, Projection );
    
	output.normal = mul(normal, (float3x3)World);

	output.tanU = tanU;
	output.texC = texC;

    return output;
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS( PS_INPUT pin ) : SV_Target
{
	// Interpolating normal can unnormalize it, so normalize it.
	
	float3 toEyeW = normalize(gEyePosW - (float3)pin.PosW);

	// Start with a sum of zero. 
	float4 ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
	float4 diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
	float4 spec    = float4(0.0f, 0.0f, 0.0f, 0.0f);

	// Sum the light contribution from each light source.
	float4 A, D, S;

	ComputeDirectionalLight(gMaterial, gDirLight, pin.normal, toEyeW, A, D, S);
	ambient += A;  
	diffuse += D;
	spec    += S;

	ComputePointLight(gMaterial, gPointLight, (float3)pin.PosW, pin.normal, toEyeW, A, D, S);
	ambient += A;
	diffuse += D;
	spec    += S;

	ComputeSpotLight(gMaterial, gSpotLight, (float3)pin.PosW, pin.normal, toEyeW, A, D, S);
	ambient += A;
	diffuse += D;
	spec    += S;

	float4 litColor = ambient + diffuse + spec;

	// Common to take alpha from diffuse material.
	litColor.a = gMaterial.Diffuse.a;
	
	//return litColor;
    return txDiffuse.Sample( samLinear, pin.texC ) * litColor;
	
	
	
	//return txDiffuse.Sample( samLinear, pin.texC);
}
