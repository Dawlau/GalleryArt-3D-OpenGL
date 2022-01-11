#pragma once
#include "Shape.h"

#include <GL/glew.h>
#include <GL/freeglut.h>
#include "glmInclude.h"

class Cone : public Shape {

private:
	float radius = 1, height = 4;
	const int Size = 50; // size on screen
	float const U_MIN = 0, U_MAX = 2 * PI, V_MIN = 0, V_MAX = 1;
	int const NUM_DIV_X = 30, NUM_DIV_Y = 1;
	float step_u = (U_MAX - U_MIN) / NUM_DIV_X, step_v = (V_MAX - V_MIN) / NUM_DIV_Y;

public:

	Cone();
	// void CreateVBO() override;
	// void DestroyVBO() override;
	void Render() override;
	void DrawShadow() override;
};