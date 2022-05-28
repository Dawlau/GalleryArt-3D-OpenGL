#include "Sphere.h"

Sphere::Sphere(const glm::vec3& scale, const glm::vec3& translation, int NUM_DIV_X, int NUM_DIV_Y, const bool& hasShadow) : Shape(scale, translation, hasShadow), NUM_DIV_X(NUM_DIV_X), NUM_DIV_Y(NUM_DIV_Y) {
	int last_index = NUM_DIV_X * (NUM_DIV_Y + 1);
	Indices.resize(4 * NUM_DIV_X * NUM_DIV_Y);

	Vertices.resize(VertexSize * NUM_DIV_X * (NUM_DIV_Y + 1));

	glm::highp_vec4 color = glm::highp_vec4(0.12f, 0.13f, 0.57f, 1.0f);

	int vertex_index = 0, indice_index = 0;

	for (int divY = 0; divY < NUM_DIV_Y + 1; divY++)
	{
		for (int divX = 0; divX < NUM_DIV_X; divX++)
		{
			float u = U_MIN + divX * step_u;
			float v = V_MIN + divY * step_v;
			float x_vf = radius * cosf(v) * cosf(u);
			float y_vf = radius * cosf(v) * sinf(u);
			float z_vf = radius * sinf(v);

			Vertices[vertex_index] = x_vf; Vertices[vertex_index + 1] = y_vf; Vertices[vertex_index + 2] = z_vf; Vertices[vertex_index + 3] = 1.0f;
			vertex_index += 4;
			Vertices[vertex_index] = color.r; Vertices[vertex_index + 1] = color.g; Vertices[vertex_index + 2] = color.b; Vertices[vertex_index + 3] = color.a;
			vertex_index += 4;
			Vertices[vertex_index] = x_vf; Vertices[vertex_index + 1] = y_vf; Vertices[vertex_index + 2] = z_vf;
			vertex_index += 3;
			if (divY < NUM_DIV_Y)
			{
				int currentIndex = divY * NUM_DIV_X + divX;
				int rightIndex = divY * NUM_DIV_X + (divX + 1) % NUM_DIV_X;
				int topRightIndex = (divY + 1) * NUM_DIV_X + (divX + 1) % NUM_DIV_X;
				int topIndex = (divY + 1) * NUM_DIV_X + divX;
				Indices[indice_index] = currentIndex;
				Indices[indice_index + 1] = rightIndex;
				Indices[indice_index + 2] = topRightIndex;
				Indices[indice_index + 3] = topIndex;
				indice_index += 4;
			}
		}
	}

	Color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
}

void Sphere::Render() {

	CreateVBO();
	glDrawElements(GL_QUADS, 4 * NUM_DIV_X * NUM_DIV_Y, GL_UNSIGNED_SHORT, (void*)(0));
	if (!hasShadow) {
		DestroyVBO();
	}
}

void Sphere::DrawShadow() {
	glDrawElements(GL_QUADS, 4 * NUM_DIV_X * NUM_DIV_Y, GL_UNSIGNED_SHORT, (void*)(0));
	DestroyVBO();
}