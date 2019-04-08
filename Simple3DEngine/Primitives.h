#pragma once

#include <vector>

struct Vec3d
{
	float x, y, z;
};

struct Triangle
{
	const static short VERTEXES = 3;
	Vec3d p[3];
};

struct Mesh
{
	std::vector<Triangle> triangles;
};

struct Matrix4x4
{
	float m[4][4] = { 0 };
};

Vec3d multiplyVectorByMatrix(Vec3d& vector, Matrix4x4& matrix);

