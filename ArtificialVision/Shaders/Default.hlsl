
cbuffer PARAMS:register(b0){ //constant buffer valor inicial es 0
	//Variable declarada (global) cpu puede guardarlo
	matrix T;
	float time;
	//Para dejar explicito que queremos usar un registro.
};

Texture2D<float4> Input:register(t0);
RWTexture2D<float4> Output:register(u0);//UAV

float4 BilinealSampler(float2 uv){
	uv -= float2(0.5, 0.5);//Calcular centro de pixel.
	int2 ij = int2(uv);//Extraer parte entera de las del texel de referencia mas cercano
	float4 A, B, C, D;
	int2 coord;
	int2 size;
	
	Input.GetDimensions(size.x,size.y);
	coord = ij;
	coord = max(int2(0, 0), coord);
	coord = min(size-int2(2,2), coord);

	A = Input[coord];
	B = Input[coord + int2(1, 0)];
	C = Input[coord + int2(0, 1)];
	D = Input[coord + int2(1, 1)];

	float2 pq = uv - ij;//Parte entera -parte entera-fraccional=parte fraccional.
	float4 J, K;
	J = A + pq.x*(B - A);//Ecuacion general de la interpolacion lineal.
	K = C + pq.x*(D - C);
	return J + pq.y*(K - J);
}

[numthreads(8, 8, 1)]
void CSMain(uint3 id:SV_DispatchThreadID)
{
		float4 position = float4(id.xy, 0, 1);
		position = mul(position, T);
		//Filtrado Bilineal
		Output[id.xy] = BilinealSampler(position.xy);
		/*float2(0.1*cos(Time)+0.1*sin(Time))*/
	/*Output[id.xy] = Input[int2(position.xy)];*/
	/*Coord.x = id.x + 10 * cos(0.1*id.x + 10 * time);
	Coord.y = id.y + 10 * sin(0.1*id.y + 10 * time);
	
	Output[id.xy] = float4(1,sin(0.01*id.x),cos(0.001*id.x*id.y),1)*Input[Coord];*/
}
