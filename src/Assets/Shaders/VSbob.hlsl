#pragma pack_matrix(row_major)
cbuffer MatrixBuffer
{
    float4x4 worldMatrix;
    float4x4 viewMatrix;
    float4x4 projectionMatrix;
}


struct VS_INPUT
{
    float3 position : POSITION;
    float2 uv : TEXCOORD0;
    float3 normal : NORMAL;
};
struct VS_OUTPUT
{
    float4 position : SV_POSITION;
    float2 uv : TEXCOORD0;
    float3 normal : NORMAL;
};

VS_OUTPUT main(const VS_INPUT _input)
{
    VS_OUTPUT output;
    output.position = mul(float4(_input.position.xyz, 1.0f), worldMatrix );
    output.position = mul(output.position, viewMatrix);
    output.position = mul(output.position, projectionMatrix);

    output.uv = _input.uv;

    output.normal = mul(_input.normal, float3x3(worldMatrix[0].xyz, worldMatrix[1].xyz, worldMatrix[2].xyz));
    return output;
}
