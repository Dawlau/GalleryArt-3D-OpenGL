#pragma once
#include "Shape.h"

#include <GL/glew.h>
#include <GL/freeglut.h>
#include "glmInclude.h"

class Cylinder : public Shape {

private:
	float radius = 50, height = 200;
	const int Size = 50; // size on screen
	float const U_MIN = 0, U_MAX = 2 * PI, V_MIN = 0, V_MAX = 1;
	int const NR_PARR = 2, NR_MERID = 2;
	float step_u = (U_MAX - U_MIN) / NR_PARR, step_v = (V_MAX - V_MIN) / NR_MERID;

public:

	Cylinder();
	// void CreateVBO() override;
	// void DestroyVBO() override;
	void Render() override;
};