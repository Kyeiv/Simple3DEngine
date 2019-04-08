#pragma once

#include "olcConsoleGameEngineGLOOP.h"
#include "Primitives.h"

class Engine : public olcConsoleGameEngineGLOOP
{
	Mesh      _meshCube;
	Matrix4x4 _projectionMatrix;
	float     _rotationAngle;
public:
	Engine();
	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTime) override;
	void DrawTriangle(Triangle projectedTriangle, short mode, short color);
	~Engine();
};

