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

	float xScale, yScale, zScale;
	float xTranslation, yTranslation, zTranslation;

	Shape(const bool& = true);

	virtual void CreateVBO();
	virtual void DestroyVBO();

public:

	virtual void Render() = 0;
	virtual void DrawShadow() = 0;

	glm::vec4 getColor();
	bool getHasShadow();
};