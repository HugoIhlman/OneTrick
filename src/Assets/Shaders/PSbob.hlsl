Texture2D shaderTexture : register(t0);
SamplerState SampleType : register(s0);

cbuffer LightBuffer
{
    float4 diffuseColor;
    float3 lightDirection;
    float padding;
}

struct PS_INPUT
{
    float4 position : SV_POSITION;
    float2 uv : TEXCOORD0;
    float3 normal : NORMAL;
};

struct PS_OUTPUT
{
    float4 color : SV_TARGET;
};

PS_OUTPUT main(const PS_INPUT _input)
{
    PS_OUTPUT output;
    float4 lightColor;
    float4 texColor;
    float3 lightDir;
    float intensity;
    texColor = shaderTexture.Sample(SampleType, _input.uv);

    lightDir = -lightDirection;
    intensity = saturate(dot(normalize(_input.normal), lightDir));
    lightColor = saturate(diffuseColor * intensity);

    output.color = lightColor * texColor;
    output.color.a = 1.0f;
    
    return output;
}
