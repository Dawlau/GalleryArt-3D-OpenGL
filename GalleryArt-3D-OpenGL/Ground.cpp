#include "Ground.h"

Ground::Ground() {

	Vertices = {
		-5.0f, -5.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		5.0f, -5.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		5.0f, 5.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		-5.0f, 5.0f, 0.0f,1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	};

	Color = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
}

void Ground::Render() {

	CreateVBO();
	glDrawArrays(GL_POLYGON, 0, Vertices.size());
	DestroyVBO();
}