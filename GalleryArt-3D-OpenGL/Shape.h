#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <vector>
#include "glmInclude.h"

class Shape {

protected:
	static constexpr float PI = 3.141592f;
	/*
		4 - positions
		4 - colors
		3 - normals
	*/
	static const int VertexSize = 11;

	std::vector <float> Vertices;
	std::vector <GLushort> Indices;
	bool hasShadow;

	GLuint VaoId;
	GLuint VboId;
	GLuint EboId;

	glm::vec4 Color;

	glm::mat4 scaleMatrix;
	glm::mat4 translationMatrix;

	Shape(const glm::vec3& = glm::vec3(1.0f, 1.0f, 1.0f), const glm::vec3& = glm::vec3(0.0f, 0.0f, 0.0f), const bool& = true);

	virtual void CreateVBO();
	virtual void DestroyVBO();

public:

	virtual void Render() = 0;
	virtual void DrawShadow() = 0;

	glm::vec4 getColor();
	bool getHasShadow();

	glm::mat4 getScale();
	glm::mat4 getTranslation();
};