cbuffer PARAMS{
	unsigned int option;
	float THRESHOLD;
};

Texture2D<float4> InputA:register(t0);
Texture2D<float4> InputB:register(t1);
RWTexture2D<float4> Output:register(u0);

[numthreads(8, 8, 1)]

void CopyMain(uint3 id:SV_DispatchThreadID){
	Output[id.xy] = InputA[id.xy];
}

[numthreads(8, 8, 1)]
void NotMain(uint3 id:SV_DispatchThreadID){
	uint4 Y = uint4(255 * InputA[id.xy]);
	Y = 255 - Y;
	float4 X = float4(Y / 255.0);
	Output[id.xy] = X;
}

[numthreads(8, 8, 1)]
void AndMain(uint3 id:SV_DispatchThreadID){
	uint4 Y = uint4(255 * InputA[id.xy]);
	uint4 Z = uint4(255 * InputB[id.xy]);
	uint4 X = Y&Z;
	float4 temp = float4(X / 255.0);
	Output[id.xy] = temp;
}

[numthreads(8, 8, 1)]
void OrMain(uint3 id:SV_DispatchThreadID){
	uint4 Y = uint4(255 * InputA[id.xy]);
		uint4 Z = uint4(255 * InputB[id.xy]);
		uint4 X = Y | Z;
		float4 temp = float4(X / 255.0);
		Output[id.xy] = temp;
}

[numthreads(8, 8, 1)]
void XorMain(uint3 id:SV_DispatchThreadID){
	uint4 Y = uint4(255 * InputA[id.xy]);
		uint4 Z = uint4(255 * InputB[id.xy]);
		uint4 X = Y ^ Z;
		float4 temp = float4(X / 255.0);
		Output[id.xy] = temp;
}

[numthreads(8, 8, 1)]
void SADDMain(uint3 id:SV_DispatchThreadID){
	
	Output[id.xy] = InputA[id.xy]+InputB[id.xy];
}

[numthreads(8, 8, 1)]
void SSUBMain(uint3 id:SV_DispatchThreadID){
	Output[id.xy] = InputA[id.xy] - InputB[id.xy];
}

[numthreads(8, 8, 1)]
void ModMain(uint3 id:SV_DispatchThreadID){
	Output[id.xy] = InputA[id.xy] * InputB[id.xy];
}

[numthreads(8, 8, 1)]
void ALPHAS0Main(uint3 id:SV_DispatchThreadID){
	Output[id.xy] = (InputA[id.xy]*(InputA[id.xy].a) + (InputB[id.xy]*(1 - InputA[id.xy].a)));
}

[numthreads(8, 8, 1)]
void ALPHAS1Main(uint3 id:SV_DispatchThreadID){
	Output[id.xy] = (InputA[id.xy]*(InputA[id.xy].a) + (InputB[id.xy]*(1 - InputA[id.xy].a)));
}

[numthreads(8, 8, 1)]
void HP_THRESHOLDMain(uint3 id:SV_DispatchThreadID){
	float4 xdot = dot(InputA[id.xy], float4(0.3, 0.5, 0.2, 0)) > float4(THRESHOLD, THRESHOLD, THRESHOLD, THRESHOLD) ? InputA[id.xy] : float4(0, 0, 0, 0);
	Output[id.xy] = xdot;
}

[numthreads(8, 8, 1)]
void LP_THRESHOLDMain(uint3 id:SV_DispatchThreadID){

	float4 xdot = dot(InputA[id.xy], float4(0.3, 0.5, 0.2, 0)) < float4(THRESHOLD, THRESHOLD, THRESHOLD, THRESHOLD) ? InputA[id.xy] : float4(0, 0, 0, 0);
	Output[id.xy] = xdot;
}

[numthreads(8, 8, 1)]
void MergeMain(uint3 id:SV_DispatchThreadID){
	float4 Y = InputA[id.xy] + InputB[id.xy];
		float4 Z = InputA[id.xy] * InputB[id.xy];
		float4 X = Y + Z;
	Output[id.xy] = X;

}


