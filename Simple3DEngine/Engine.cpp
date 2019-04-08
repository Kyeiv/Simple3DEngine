#define _USE_MATH_DEFINES

#include "Engine.h"
#include <math.h>



Engine::Engine()
{
	m_sAppName = L"3D_engine";
}


Engine::~Engine()
{
}

bool Engine::OnUserCreate()
{
	_meshCube.triangles = {
		// SOUTH
		{ 0.0f, 0.0f, 0.0f,    0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 0.0f, 0.0f },

		// EAST                                                      
		{ 1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f },
		{ 1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f, 1.0f },

		// NORTH                                                     
		{ 1.0f, 0.0f, 1.0f,    1.0f, 1.0f, 1.0f,    0.0f, 1.0f, 1.0f },
		{ 1.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 0.0f, 1.0f },

		// WEST                                                      
		{ 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 0.0f,    0.0f, 0.0f, 0.0f },

		// TOP                                                       
		{ 0.0f, 1.0f, 0.0f,    0.0f, 1.0f, 1.0f,    1.0f, 1.0f, 1.0f },
		{ 0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 1.0f, 0.0f },

		// BOTTOM                                                    
		{ 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f },
		{ 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f },

	};

	//Projection Matrix
	float nearestZPointCoordinate = 0.1f;
	float farestZPointCoordinate  = 1000.0f;
	float fieldOfView			  = 90.0f;
	float screenAspectRatio		  = static_cast<float>(ScreenHeight()) / static_cast<float>(ScreenWidth());
	float fieldOfViewScalingRatio = 1.0f / tanf(fieldOfView*0.5f / 180.0f*M_PI);

	_projectionMatrix.m[0][0] = screenAspectRatio * fieldOfViewScalingRatio;
	_projectionMatrix.m[1][1] = fieldOfViewScalingRatio;
	_projectionMatrix.m[2][2] = farestZPointCoordinate / (farestZPointCoordinate - nearestZPointCoordinate);
	_projectionMatrix.m[3][2] = (-farestZPointCoordinate * nearestZPointCoordinate) / (farestZPointCoordinate - nearestZPointCoordinate);
	_projectionMatrix.m[2][3] = 1.0f;
	_projectionMatrix.m[3][3] = 0.0f;

	return true;
}

bool Engine::OnUserUpdate(float fElapsedTime)
{
	//Clear the screen
	Fill(0, 0, ScreenWidth(), ScreenHeight(), PIXEL_SOLID, FG_BLACK);

	Matrix4x4 matrixRotatingXAxis, matrixRotatingZAxis;
	_rotationAngle += 1.0f * fElapsedTime;

	// Rotation Z
	matrixRotatingZAxis.m[0][0] = cosf(_rotationAngle);
	matrixRotatingZAxis.m[0][1] = sinf(_rotationAngle);
	matrixRotatingZAxis.m[1][0] = -sinf(_rotationAngle);
	matrixRotatingZAxis.m[1][1] = cosf(_rotationAngle);
	matrixRotatingZAxis.m[2][2] = 1;
	matrixRotatingZAxis.m[3][3] = 1;

	// Rotation X
	matrixRotatingXAxis.m[0][0] = 1;
	matrixRotatingXAxis.m[1][1] = cosf(_rotationAngle * 0.5f);
	matrixRotatingXAxis.m[1][2] = sinf(_rotationAngle * 0.5f);
	matrixRotatingXAxis.m[2][1] = -sinf(_rotationAngle * 0.5f);
	matrixRotatingXAxis.m[2][2] = cosf(_rotationAngle * 0.5f);
	matrixRotatingXAxis.m[3][3] = 1;

	//Draw Triangles
	for (auto triangle : _meshCube.triangles)
	{
		Triangle projectedTriangle;
		
		for (short i = 0; i < projectedTriangle.VERTEXES; i++)
		{
			//Rotating 
			triangle.p[i] = multiplyVectorByMatrix(triangle.p[i], matrixRotatingZAxis);
			triangle.p[i] = multiplyVectorByMatrix(triangle.p[i], matrixRotatingXAxis);

			//Translating triangle
			triangle.p[i].z += 3.0f;

			//Projecting
			projectedTriangle.p[i] = multiplyVectorByMatrix(triangle.p[i], _projectionMatrix);

			//Scale to view
			projectedTriangle.p[i].x += 1.0f; projectedTriangle.p[i].y += 1.0f;
			projectedTriangle.p[i].x *= 0.5f * static_cast<float>(ScreenWidth()); 
			projectedTriangle.p[i].y *= 0.5f * static_cast<float>(ScreenHeight());
		}
				
		DrawTriangle(projectedTriangle, PIXEL_SOLID, FG_WHITE);
	}
	

	return true;
}

void Engine::DrawTriangle(Triangle projectedTriangle, short mode, short color)
{
	olcConsoleGameEngineGLOOP::DrawTriangle(
		projectedTriangle.p[0].x, projectedTriangle.p[0].y,
		projectedTriangle.p[1].x, projectedTriangle.p[1].y,
		projectedTriangle.p[2].x, projectedTriangle.p[2].y,
		mode,
		color
	);
}
