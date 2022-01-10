#include "Shape.h"

Shape::Shape() {}

void Shape::CreateVBO() {

	float VertexBuffer[Vertices.size() * VertexSize];

	for(int i = 0; i < Vertices.size(); i++) {
		VertexBuffer[i] = Vertices[i];
	}

	glGenVertexArrays(1, &VaoId);
	glGenBuffers(1, &VboId);

	glBindVertexArray(VaoId);
	glBindBuffer(GL_ARRAY_BUFFER, VboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexBuffer), VertexBuffer, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0); // position
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, VertexSize * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(1); // color
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, VertexSize * sizeof(GLfloat), (GLvoid*)(4 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2); // normal
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, VertexSize * sizeof(GLfloat), (GLvoid*)(8 * sizeof(GLfloat)));
}

void Shape::DestroyVBO() {

	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &VboId);
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VaoId);
}