//#include "skinningHF.hlsli"
#include "windHF.hlsli"
#include "effectInputLayoutHF.hlsli"

cbuffer constantBuffer:register(b0){
	float4x4 xViewProjection;
	float3 xWind;
	float time;
	float windRandomness,windWaveSize;
}

cbuffer matBuffer:register(b1){
	float4 diffuseColor;
	float4 hasRefNorTexSpe;
	float4 specular;
	float4 refractionIndexMovingTexEnv;
	uint shadeless;
	uint specular_power;
	uint toonshaded;
	uint matIndex;
};


struct VertextoPixel
{
	float4 pos				: SV_POSITION;
	float2 tex				: TEXCOORD0;
};

VertextoPixel main(Input input)
{
	VertextoPixel Out = (VertextoPixel)0;

	[branch]if((uint)input.tex.z == matIndex){
		
		float4x4 WORLD = float4x4(
				float4(input.wi0.x,input.wi1.x,input.wi2.x,0)
				,float4(input.wi0.y,input.wi1.y,input.wi2.y,0)
				,float4(input.wi0.z,input.wi1.z,input.wi2.z,0)
				,float4(input.wi0.w,input.wi1.w,input.wi2.w,1)
			);

		float4 pos = input.pos;
		
//#ifdef SKINNING_ON
//		Skinning(pos,input.bon,input.wei);
//#endif
		pos=mul(pos,WORLD);
		affectWind(pos.xyz,xWind,time,input.tex.w,input.id,windRandomness,windWaveSize);

		Out.pos = mul( pos, xViewProjection );
		Out.tex = input.tex.xy;

	}

	return Out;
}