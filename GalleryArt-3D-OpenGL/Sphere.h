#pragma once
#include "Shape.h"

#include <GL/glew.h>
#include <GL/freeglut.h>
#include "glmInclude.h"

class Sphere : public Shape {

private:
	float radius = 1, height = 4;
	const int Size = 50; // size on screen
	float const U_MIN = 0, U_MAX = 2 * PI, V_MIN = -50, V_MAX = 50;
	int const NUM_DIV_X = 30, NUM_DIV_Y = 30;
	float step_u = (U_MAX - U_MIN) / NUM_DIV_X, step_v = (V_MAX - V_MIN) / NUM_DIV_Y;

public:

	Sphere();
	// void CreateVBO() override;
	// void DestroyVBO() override;
	void Render() override;
	void DrawShadow() override;
};