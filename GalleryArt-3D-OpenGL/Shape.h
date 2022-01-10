#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <vector>

class Shape {

protected:

	/*
		4 - positions
		4 - colors
		3 - normals
	*/
	static const int VertexSize = 11;

	std::vector <float> Vertices;

	GLuint VaoId;
	GLuint VboId;

	Shape();

	virtual void CreateVBO();
	virtual void DestroyVBO();
	virtual void Render() = 0;
};