#include "Ground.h"

Ground::Ground(const glm::vec3& scale, const glm::vec3& translation, const bool& hasShadow) : Shape(scale, translation, hasShadow) {

	Vertices = {
		-5.0f, -5.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		5.0f, -5.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		5.0f, 5.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		-5.0f, 5.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	};
}

void Ground::Render()
{
	CreateVBO();
	glDrawArrays(GL_QUADS, 0, 4);
	DestroyVBO();
}

void Ground::DrawShadow() {}