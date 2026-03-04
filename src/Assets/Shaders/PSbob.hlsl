Texture2D shaderTexture : register(t0);
SamplerState SampleType : register(s0);

struct PS_INPUT
{
    float4 position : SV_POSITION;
    float2 uv : TEXCOORD0;
};

float4 main(const PS_INPUT _input) : SV_TARGET
{
    float4 color;
    color = shaderTexture.Sample(SampleType, _input.uv);
    return color;
}
