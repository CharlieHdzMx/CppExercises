
cbuffer PARAMS{
	matrix Kernel;
	float4 C;
};

Texture2D<float4> Input:register(t0);
RWTexture2D<float4> Output:register(u0);

[numthreads(8,8,1)]
void Main(uint3 id:SV_DispatchThreadID){
	
	float4 Color = 0;
	for (int j = 0; j < 3;j++)
		for (int i = 0; i < 3; i++)
			Color += Kernel[i][j] * Input[int2(id.xy) + int2(i,j) - int2(1, 1)];
	
	Output[id.xy] = Color + C;

}