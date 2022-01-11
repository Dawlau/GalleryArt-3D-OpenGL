#include "Cube.h"

Cube::Cube() {

	Vertices = {
		// vertices					 // colors                // normals
		-5.0f,  -5.0f, 1.0f, 1.0f,  1.0f, 0.5f, 0.2f, 1.0f,  -1.0f, -1.0f, -1.0f,
        5.0f,  -5.0f,  1.0f, 1.0f,  1.0f, 0.5f, 0.2f, 1.0f,  1.0f, -1.0f, -1.0f,
        5.0f,  5.0f,  1.0f, 1.0f,   1.0f, 0.5f, 0.2f, 1.0f,  1.0f, 1.0f, -1.0f,
        -5.0f,  5.0f, 1.0f, 1.0f,   1.0f, 0.5f, 0.2f, 1.0f,  -1.0f, 1.0f, -1.0f,
        -5.0f,  -5.0f, 11.0f, 1.0f,  1.0f, 0.5f, 0.2f, 1.0f,  -1.0f, -1.0f, 1.0f,
        5.0f,  -5.0f,  11.0f, 1.0f,  1.0f, 0.5f, 0.2f, 1.0f,  1.0f, -1.0f, 1.0f,
        5.0f,  5.0f,  11.0f, 1.0f,   1.0f, 0.5f, 0.2f, 1.0f,  1.0f, 1.0f, 1.0f,
        -5.0f,  5.0f, 11.0f, 1.0f,   1.0f, 0.5f, 0.2f, 1.0f,  -1.0f, 1.0f, 1.0f,
	};

    Indices = {
		1, 0, 3, 2,
		2, 3, 7, 6,
		7, 3, 0, 4,
		4, 0, 1, 5,
		1, 2, 6, 5,
		5, 6, 7, 4,
    };

	Color = glm::vec4(0.2f, 0.6f, 0.1f, 1.0f);
}

void Cube::Render()
{
	CreateVBO();
	glDrawElements(GL_QUADS, 4 * 6, GL_UNSIGNED_SHORT, (void*)(0));
	if (!hasShadow) {
		DestroyVBO();
	}
}

void Cube::DrawShadow() {
	glDrawElements(GL_QUADS, 4 * 6, GL_UNSIGNED_SHORT, (void*)(0));
	DestroyVBO();
}