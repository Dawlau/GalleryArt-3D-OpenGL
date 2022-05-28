#pragma once
#include "Shape.h"

#include <GL/glew.h>
#include <GL/freeglut.h>
#include "glmInclude.h"

class Ground : public Shape {

private:

	const int Size = 50; // size on screen

public:

	Ground(const glm::vec3& = glm::vec3(1.0f, 1.0f, 1.0f), const glm::vec3& = glm::vec3(0.0f, 0.0f, 0.0f), const bool& = true);
	// void CreateVBO() override;
	// void DestroyVBO() override;
	void Render() override;
	void DrawShadow() override;
};