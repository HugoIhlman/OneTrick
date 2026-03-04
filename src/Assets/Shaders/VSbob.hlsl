cbuffer MatrixBuffer
{
    matrix worldMatrix;
    matrix viewMatrix;
    matrix projectionMatrix;
}


struct VS_INPUT
{
    float3 position : POSITION;
    float2 uv : TEXCOORD0;
};
struct VS_OUTPUT
{
    float4 position : SV_POSITION;
    float2 uv : TEXCOORD0;
};

VS_OUTPUT main(const VS_INPUT _input)
{
    VS_OUTPUT output;
    output.position = mul(_input.position, worldMatrix);
    output.position = mul(output.position, viewMatrix);
    output.position = mul(output.position, projectionMatrix);
    output.position.w = 1.0f;

    output.uv = _input.uv;
    return output;
}
