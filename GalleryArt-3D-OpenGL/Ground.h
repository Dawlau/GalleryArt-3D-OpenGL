#pragma once
#include "Shape.h"

#include <GL/glew.h>
#include <GL/freeglut.h>
#include "glmInclude.h"

class Ground : public Shape {

private:

	const int Size = 20; // size on screen

public:

	Ground();
	// void CreateVBO() override;
	// void DestroyVBO() override;
	void Render() override;
};