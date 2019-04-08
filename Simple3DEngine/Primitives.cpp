#include "Primitives.h"

Vec3d multiplyVectorByMatrix(Vec3d& vector, Matrix4x4& matrix)
{
	//Implying that hidden 4th element of the input vector is equal to 1
	Vec3d resultVector;
	resultVector.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + matrix.m[3][0];
	resultVector.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + matrix.m[3][1];
	resultVector.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + matrix.m[3][2];
	float additionalForthVectorElement = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + matrix.m[3][3];

	if (additionalForthVectorElement != 0.0f)
	{
		resultVector.x /= additionalForthVectorElement; 
		resultVector.y /= additionalForthVectorElement; 
		resultVector.z /= additionalForthVectorElement;
	}

	return resultVector;
}