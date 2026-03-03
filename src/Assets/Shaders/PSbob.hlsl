struct PS_INPUT
{
    float4 position : SV_POSITION;
    float3 color : COLOR;
};

float4 main(const PS_INPUT _input) : SV_TARGET
{
    return float4(_input.color, 1.0);
}
