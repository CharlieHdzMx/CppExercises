#include "stdafx.h"
#include "matrix.h"
#include <math.h>

float dot(VECTOR4D& A, VECTOR4D& B){
	return ((A.x*B.x) + (A.y*B.y) + (A.z*B.z) + (A.w*B.w));
}

VECTOR4D cross3(VECTOR4D& A, VECTOR4D& B){
	VECTOR4D C;
	C.x = ((A.y*B.z) - (A.z*B.y));
	C.y = ((A.x*B.z) - (A.z*B.x));
	C.z = ((A.x*B.y) - (A.y*B.x));
	C.w = 0;
	return C;
}

VECTOR4D operator*(VECTOR4D& A, VECTOR4D& B){
	VECTOR4D C;
	C.x = A.x*B.x;
	C.y = A.y*B.y;
	C.z = A.z*B.z;
	C.w = A.w*B.w;
	return C;
}

VECTOR4D operator*(VECTOR4D& A, float s){
	VECTOR4D C;
	C.x = A.x*s;
	C.y = A.y*s;
	C.z = A.z*s;
	C.w = A.w*s;
	return C;
}

VECTOR4D operator+(VECTOR4D& A, VECTOR4D& B){
	VECTOR4D C;
	C.x = A.x + B.x;
	C.y = A.y + B.y;
	C.z = A.z + B.z;
	C.w = A.w + B.w;
	return C;
}

float  SgMag(VECTOR4D& A){
	return dot(A, A);
}

//Matrices
MATRIX4D identity(){
	MATRIX4D I;
	I = zero();
	I.m[0][0] = 1;
	I.m[1][1] = 1;
	I.m[2][2] = 1;
	I.m[3][3] = 1;
	return I;
}

MATRIX4D zero(){
	MATRIX4D Z;
	for (unsigned int i = 0; i < 4; i++){
		for (unsigned int j = 0; j < 4; j++){
			Z.m[i][j] = 0;
		}
	}
	return Z;
}

MATRIX4D rotationX(float theta){
	MATRIX4D A= { 1, 0, 0, 0,
				   0, cos(theta), sin(theta), 0, 
				   0, -sin(theta), cos(theta), 0,
				   0, 0, 0, 1 };
	return A;
}

MATRIX4D rotationY(float theta){
	MATRIX4D A = { cos(theta), 0, -sin(theta), 0,
		0, 1, 0, 0,
		sin(theta), 0, cos(theta), 0,
		0, 0, 0, 1 };
	return A;
}

MATRIX4D rotationZ(float theta){
	MATRIX4D A = { cos(theta), sin(theta), 0, 0,
		-sin(theta), cos(theta), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1 };
	return A;
}

MATRIX4D operator*(MATRIX4D& A, MATRIX4D& B){
	MATRIX4D C;

	C.m00 = ((A.m00*B.m00) + (A.m01*B.m10) + (A.m02*B.m20) + (A.m03*B.m30));
	C.m01 = ((A.m00*B.m01) + (A.m01*B.m11) + (A.m02*B.m21) + (A.m03*B.m31));
	C.m02 = ((A.m00*B.m02) + (A.m01*B.m12) + (A.m02*B.m22) + (A.m03*B.m32));
	C.m03 = ((A.m00*B.m03) + (A.m01*B.m13) + (A.m02*B.m23) + (A.m03*B.m33));

	C.m10 = ((A.m10*B.m00) + (A.m11*B.m10) + (A.m12*B.m20) + (A.m13*B.m30));
	C.m11 = ((A.m10*B.m01) + (A.m11*B.m11) + (A.m12*B.m21) + (A.m13*B.m31));
	C.m12 = ((A.m10*B.m02) + (A.m11*B.m12) + (A.m12*B.m22) + (A.m13*B.m32));
	C.m13 = ((A.m10*B.m03) + (A.m11*B.m13) + (A.m12*B.m23) + (A.m13*B.m33));

	C.m20 = ((A.m20*B.m00) + (A.m21*B.m10) + (A.m22*B.m20) + (A.m23*B.m30));
	C.m21 = ((A.m20*B.m01) + (A.m21*B.m11) + (A.m22*B.m21) + (A.m23*B.m31));
	C.m22 = ((A.m20*B.m02) + (A.m21*B.m12) + (A.m22*B.m22) + (A.m23*B.m32));
	C.m23 = ((A.m20*B.m03) + (A.m21*B.m13) + (A.m22*B.m23) + (A.m23*B.m33));

	C.m30 = ((A.m30*B.m00) + (A.m31*B.m10) + (A.m32*B.m20) + (A.m33*B.m30));
	C.m31 = ((A.m30*B.m01) + (A.m31*B.m11) + (A.m32*B.m21) + (A.m33*B.m31));
	C.m32 = ((A.m30*B.m02) + (A.m31*B.m12) + (A.m32*B.m22) + (A.m33*B.m32));
	C.m33 = ((A.m30*B.m03) + (A.m31*B.m13) + (A.m32*B.m23) + (A.m33*B.m33));

	return C;
}

VECTOR4D operator*(VECTOR4D& V, MATRIX4D& M){
	VECTOR4D C;
	C.x= ((V.x*M.m00) + (V.y*M.m10)+(V.z*M.m20) + (V.w*M.m30));
	C.y = ((V.x*M.m01) + (V.y*M.m11) + (V.z*M.m21) + (V.w*M.m31));
	C.z = ((V.x*M.m02) + (V.y*M.m12) + (V.z*M.m22) + (V.w*M.m32));
	C.w = ((V.x*M.m03) + (V.y*M.m13) + (V.z*M.m23) + (V.w*M.m33));
	return C;
}

MATRIX4D transpose(MATRIX4D& M){
	MATRIX4D C = M;
	C.m01 = M.m10; C.m02 = M.m20; C.m03 = M.m30;
	C.m10 = M.m01; C.m12 = M.m21; C.m13 = M.m31;
	C.m20 = M.m02; C.m21 = M.m12; C.m23 = M.m32;
	C.m30 = M.m03; C.m31 = M.m13; C.m32 = M.m23;
	return C;
}

float det(MATRIX4D& A){
	float det;

	det = (A.m00*((A.m11*(A.m22*A.m33 - A.m23*A.m32)) - (A.m12*(A.m21*A.m33 - A.m31*A.m23)) + (A.m13*(A.m21*A.m32 - A.m22*A.m31))))
		- (A.m01*((A.m10*(A.m22*A.m33 - A.m23*A.m32)) - (A.m12*(A.m20*A.m33 - A.m23*A.m30)) + (A.m13*(A.m20*A.m32 - A.m22*A.m30))))
		+ (A.m02*((A.m10*(A.m21*A.m33 - A.m23*A.m31)) - (A.m11*(A.m20*A.m33 - A.m23*A.m30)) + (A.m13*(A.m20*A.m31 - A.m30*A.m21))))
		- (A.m03*((A.m10*(A.m21*A.m32 - A.m22*A.m31)) - (A.m11*(A.m20*A.m32 - A.m22*A.m30)) + (A.m12*(A.m20*A.m31 - A.m21*A.m30))));
	return det;
}

MATRIX4D inverse(MATRIX4D& M){
	MATRIX4D A = M;
	MATRIX4D C;
	
	//Adjunta
	C.m00 = ((A.m11*(A.m22*A.m33 - A.m23*A.m32)) - (A.m12*(A.m21*A.m33 - A.m31*A.m23)) + (A.m13*(A.m21*A.m32 - A.m22*A.m31)));
	C.m01 = -((A.m10*(A.m22*A.m33 - A.m23*A.m32)) - (A.m12*(A.m20*A.m33 - A.m23*A.m30)) + (A.m13*(A.m20*A.m32 - A.m22*A.m30)));
	C.m02 = ((A.m10*(A.m21*A.m33 - A.m23*A.m31)) - (A.m11*(A.m20*A.m33 - A.m23*A.m30)) + (A.m13*(A.m20*A.m31 - A.m30*A.m21)));
	C.m03 = -((A.m10*(A.m21*A.m32 - A.m22*A.m31)) - (A.m11*(A.m20*A.m32 - A.m22*A.m30)) + (A.m12*(A.m20*A.m31 - A.m21*A.m30)));

	C.m10 = -((A.m01*(A.m22*A.m33 - A.m23*A.m32)) - (A.m02*(A.m21*A.m33 - A.m31*A.m23)) + (A.m03*(A.m21*A.m32 - A.m22*A.m31)));
	C.m11 = ((A.m00*(A.m22*A.m33 - A.m23*A.m32)) - (A.m02*(A.m20*A.m33 - A.m23*A.m30)) + (A.m03*(A.m20*A.m32 - A.m22*A.m30)));
	C.m12 = -((A.m00*(A.m21*A.m33 - A.m23*A.m31)) - (A.m01*(A.m20*A.m33 - A.m23*A.m30)) + (A.m03*(A.m20*A.m31 - A.m30*A.m21)));
	C.m13 = ((A.m00*(A.m21*A.m32 - A.m22*A.m31)) - (A.m01*(A.m20*A.m32 - A.m22*A.m30)) + (A.m02*(A.m20*A.m31 - A.m21*A.m30)));

	C.m20 = ((A.m01*(A.m12*A.m33 - A.m13*A.m32)) - (A.m02*(A.m11*A.m33 - A.m31*A.m13)) + (A.m03*(A.m11*A.m32 - A.m12*A.m31)));
	C.m21 = -((A.m00*(A.m12*A.m33 - A.m13*A.m32)) - (A.m02*(A.m10*A.m33 - A.m13*A.m30)) + (A.m03*(A.m10*A.m32 - A.m12*A.m30)));
	C.m22 = ((A.m00*(A.m11*A.m33 - A.m13*A.m31)) - (A.m01*(A.m10*A.m33 - A.m13*A.m30)) + (A.m03*(A.m10*A.m31 - A.m30*A.m11)));
	C.m23 = -((A.m00*(A.m11*A.m32 - A.m12*A.m31)) - (A.m01*(A.m10*A.m32 - A.m12*A.m30)) + (A.m02*(A.m10*A.m31 - A.m11*A.m30))) ;

	C.m30 = -((A.m01*(A.m12*A.m23 - A.m13*A.m22)) - (A.m02*(A.m11*A.m23 - A.m21*A.m13)) + (A.m03*(A.m11*A.m22 - A.m12*A.m21)));
	C.m31 = ((A.m00*(A.m12*A.m23 - A.m13*A.m22)) - (A.m02*(A.m10*A.m23 - A.m13*A.m20)) + (A.m03*(A.m10*A.m22 - A.m12*A.m20)));
	C.m32 = -((A.m00*(A.m11*A.m23 - A.m13*A.m21)) - (A.m01*(A.m10*A.m23 - A.m13*A.m20)) + (A.m03*(A.m10*A.m21 - A.m20*A.m11)));
	C.m33 = ((A.m00*(A.m11*A.m22 - A.m12*A.m21)) - (A.m01*(A.m10*A.m22 - A.m12*A.m20)) + (A.m02*(A.m10*A.m21 - A.m11*A.m20)));

	//Determinante.
	float determinant = det(A);

	C.m00 /= determinant; C.m01 /= determinant; C.m02 /= determinant; C.m03 /= determinant;
	C.m10 /= determinant; C.m11 /= determinant; C.m12 /= determinant; C.m13 /= determinant;
	C.m20 /= determinant; C.m21 /= determinant; C.m22 /= determinant; C.m23 /= determinant;
	C.m30 /= determinant; C.m31 /= determinant; C.m32 /= determinant; C.m33 /= determinant;

	C= transpose(C);
	return C;
}

MATRIX4D translation(int dx, int dy, int dz){
	MATRIX4D C={1,0,0,0,
					0,1,0,0,
					0,0,1,0,
					dx,dy,dz,1};
	return C;
}

MATRIX4D scaling(float sx, float sy, float sz){
	MATRIX4D C = identity();

	C.m00 = sx;
	C.m11 = sy;
	C.m22 = sz;
	C.m33 = 1;
	return C;
}
