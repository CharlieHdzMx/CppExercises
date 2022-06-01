#pragma once

struct VECTOR4D{
	//Members
	union{
		struct{
			float x, y, z, w;
		};
		float v[4];
	};	
	//Methods
}; 

struct MATRIX4D{
	union{
		struct{
			float m00, m01, m02,m03;
			float m10, m11, m12, m13;
			float m20, m21, m22, m23;
			float m30, m31, m32, m33;
		};
		float m[4][4];
		float v[16];

	};
};

float dot(VECTOR4D& A, VECTOR4D& B);
VECTOR4D cross3(VECTOR4D& A, VECTOR4D& B);
VECTOR4D operator*(VECTOR4D& A, VECTOR4D& B);
VECTOR4D operator*(VECTOR4D& A, float s);
VECTOR4D operator+(VECTOR4D& A, VECTOR4D& B);
MATRIX4D rotationZ(float theta);
float SgMag(VECTOR4D& A);


MATRIX4D identity();
MATRIX4D zero();
MATRIX4D rotationX(float theta);
MATRIX4D rotationY(float theta);
MATRIX4D rotationZ(float theta);
MATRIX4D operator*(MATRIX4D& A, MATRIX4D& B);
VECTOR4D operator*(VECTOR4D& V, MATRIX4D& M);
MATRIX4D operator*(MATRIX4D& M, VECTOR4D& V);
MATRIX4D transpose(MATRIX4D& M);
float det(MATRIX4D& M);
MATRIX4D inverse(MATRIX4D& M);
MATRIX4D translation(int dx, int dy, int dz);
MATRIX4D scaling(float sx, float sy, float sz);
