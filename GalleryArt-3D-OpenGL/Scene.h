#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
#include "glmInclude.h"
#include "Ground.h"
#include "Cylinder.h"

class Scene {

private:

	Scene() {

		normMatrix = glm::scale(glm::vec3(1.0f / windowWidth, 1.0f / windowHeight, 1.0f / windowHeight));
	}

	Ground ground;
	Cylinder cylinder;

	static constexpr float PI = 3.141592f;

	static const int initialWindowsPosX = 100;
	static const int initialWindowsPosY = 100;

	static const int windowWidth = 800;
	static const int windowHeight = 600;

	glm::mat4 normMatrix;
	glm::vec3 EyePosition = glm::vec3(0.0f, -1.5f, -1.0f);
	glm::vec3 ReferencePoint = glm::vec3(0.0f, 0.0f, 0.0f);

	const char* vertexShaderPath = "Shader.vert";
	const char* fragmentShaderPath = "Shader.frag";

	GLuint shadersId;

	void loadShaders();
	void unloadShaders();

public:

	Scene(Scene const&)            = delete;
    void operator =(Scene const&)  = delete;

	void setup();
	void run(int, char**);

	void cleanup();
	void render();

	static Scene& getInstance();
};

void renderWrapper();
void cleanupWrapper();