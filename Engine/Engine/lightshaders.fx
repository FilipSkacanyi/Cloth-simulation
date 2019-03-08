cbuffer ConstantBuffer : register( b0 )
{
	matrix World;
	matrix View;
	matrix Projection;
}

//--------------------------------------------------------------------------------------
struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
    float4 Color : COLOR0;
    float3 normal : NORMAL;
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
VS_OUTPUT VS( float4 Pos : POSITION, float4 Color : COLOR, float3 normal : NORMAL)
{
    VS_OUTPUT output = (VS_OUTPUT)0;
    output.Pos = mul( Pos, World );
    output.Pos = mul( output.Pos, View );
    output.Pos = mul( output.Pos, Projection );
    output.Color = Color;
    return output;
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS( VS_OUTPUT input ) : SV_Target
{
	float4 textureColor;
	float3 lightDir;
	float lightIntensity;
	float4 color;

	// Invert the light direction for calculations.
	//lightDir = -lightDirection;

	// Calculate the amount of light on this pixel.
	//lightIntensity = saturate(dot(input.normal, lightDir));

	// Determine the final amount of diffuse color based on the diffuse color combined with the light intensity.
	//color = saturate(diffuseColor * lightIntensity);

	//color = color * input.color;

    return input.Color;
}