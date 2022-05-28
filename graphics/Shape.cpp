#include "Shape.h"

Shape::Shape(const glm::vec3& scale, const glm::vec3& translation, const bool& hasShadow) {
	this->hasShadow = hasShadow;
	scaleMatrix = glm::scale(scale);
	translationMatrix = glm::translate(translation);
}

glm::vec4 Shape::getColor() {
	return Color;
}

void Shape::setColor(glm::vec4 newColor) {
	int n = int(Vertices.size() / VertexSize);
	Color = newColor;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 4; j++) {
			Vertices[i * VertexSize + 4 + j] = newColor[j];
		}
	}
}

glm::mat4 Shape::getScale() {
	return scaleMatrix;
}

glm::mat4 Shape::getTranslation() {
	return translationMatrix;
}

bool Shape::getHasShadow() {
	return hasShadow;
}

void Shape::CreateVBO() {
	glGenVertexArrays(1, &VaoId);
	glGenBuffers(1, &VboId);
	glGenBuffers(1, &EboId);

	glBindVertexArray(VaoId);
	glBindBuffer(GL_ARRAY_BUFFER, VboId);
	glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(float), Vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indices.size() * sizeof(GLushort), Indices.data(), GL_STATIC_DRAW);

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
	glDeleteBuffers(1, &EboId);
	glDeleteBuffers(1, &VboId);
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VaoId);
}