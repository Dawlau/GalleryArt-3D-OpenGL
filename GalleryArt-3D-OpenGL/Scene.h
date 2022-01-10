#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
#include "glmInclude.h"
#include "Ground.h"

class Scene {

private:

	Scene() {

		normMatrix = glm::scale(glm::vec3(2.0f / windowWidth, 2.0f / windowHeight, 1.0f)) * glm::translate(glm::vec3(-windowWidth / 2.0f, -windowHeight / 2.0f, 0.0f));
	}

	Ground ground;

	static constexpr float PI = 3.14;

	static const int initialWindowsPosX = 100;
	static const int initialWindowsPosY = 100;

	static const int windowWidth = 800;
	static const int windowHeight = 600;

	glm::mat4 normMatrix;
	glm::vec3 EyePosition = glm::vec3(0.0f, 0.0f, -800.0f);
	glm::vec3 ReferencePoint = glm::vec3(0.0f, 0.0f, 0.0f);

	const char* vertexShaderPath = "Shader.vert";
	const char* fragmentShaderPath = "Shader.frag";

	GLuint shadersId;
	GLuint normLocation;

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