#include "Cylinder.h"

Cylinder::Cylinder() {
	int last_index = (NR_PARR + 1) * NR_MERID;
	Indices.resize(2 * (NR_PARR + 1) * NR_MERID + 4 * (NR_PARR + 1) * NR_MERID);

	Vertices.resize(VertexSize * (NR_PARR + 1) * NR_MERID);

	glm::highp_vec4 color = glm::highp_vec4(0.94f, 0.73f, 0.57f, 1.0f);

	int vertex_index = 0, index_aux = 0, index = 0;

	for (int merid = 0; merid < NR_MERID; merid++)
	{
		for (int parr = 0; parr < NR_PARR + 1; parr++)
		{
			float u = U_MIN + parr * step_u;
			float v = V_MIN + merid * step_v;
			float x_vf = radius * cosf(u);
			float y_vf = radius * sinf(u);
			float z_vf = height;

			index = merid * (NR_PARR + 1) + parr;
			vertex_index = VertexSize * index;

			Vertices[vertex_index] = x_vf; Vertices[vertex_index + 1] = y_vf; Vertices[vertex_index + 2] = z_vf; Vertices[vertex_index + 3] = 1.0f;
			vertex_index += 4;
			Vertices[vertex_index] = color.r; Vertices[vertex_index + 1] = color.g; Vertices[vertex_index + 2] = color.b; Vertices[vertex_index + 3] = color.a;
			vertex_index += 4;
			Vertices[vertex_index] = x_vf; Vertices[vertex_index + 1] = y_vf; Vertices[vertex_index + 2] = -z_vf;
			Indices[merid * (NR_PARR + 1) + parr] = merid * (NR_PARR + 1) + parr;

			index_aux = parr * (NR_MERID) + merid;
			Indices[(NR_PARR + 1) * NR_MERID + index_aux] = index;

			if ((parr + 1) % (NR_PARR + 1) != 0)
			{
				int AUX = 2 * (NR_PARR + 1) * NR_MERID;
				int index1 = index;
				int index2 = index + (NR_PARR + 1);
				int index3 = index2 + 1;
				int index4 = index + 1;
				if (merid == NR_MERID - 1)
				{
					index2 = index2 % (NR_PARR + 1);
					index3 = index3 % (NR_PARR + 1);
				}
				Indices[AUX + 4 * index] = index1;
				Indices[AUX + 4 * index + 1] = index2;
				Indices[AUX + 4 * index + 2] = index3;
				Indices[AUX + 4 * index + 3] = index4;
			}
		}
	}
}

void Cylinder::Render() {

	CreateVBO();
	for (int patr = 0; patr < (NR_PARR + 1) * NR_MERID; patr++)
	{
		if ((patr + 1) % (NR_PARR + 1) != 0)
		{
			glDrawElements(GL_QUADS, 4, GL_UNSIGNED_SHORT, (GLvoid*)((2 * (NR_PARR + 1) * NR_MERID + 4 * patr) * VertexSize * sizeof(GLushort)));
		}
	}
	DestroyVBO();
}