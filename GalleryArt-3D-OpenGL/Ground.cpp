#include "Ground.h"

Ground::Ground() {

	Vertices = {
		-3200.0f, -2400.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		3200.0f, -2400.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		3200.0f, 2400.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		-3200.0f, 2400.0f, 0.0f,1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	};
}

void Ground::Render() {

	CreateVBO();
	glDrawArrays(GL_POLYGON, 0, Vertices.size());
	DestroyVBO();
}