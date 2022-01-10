#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
#include "glmInclude.h"
#include "Ground.h"
#include "Cylinder.h"

class Scene {

private:

	Scene() {}

	Ground ground;
	Cylinder cylinder;

	static constexpr float PI = 3.141592f;

	static const int initialWindowsPosX = 100;
	static const int initialWindowsPosY = 100;

	static const int windowWidth = 800;
	static const int windowHeight = 600;

	glm::vec3 EyePosition = glm::vec3(0.0f, -10.5f, 1.0f);
	glm::vec3 ReferencePoint = glm::vec3(0.0f, 0.0f, 0.0f);

	const char* vertexShaderPath = "Shader.vert";
	const char* fragmentShaderPath = "Shader.frag";

	GLuint shadersId;
	GLuint objectColorLoc;
	GLuint lightColorLoc;
	GLuint lightPosLoc;
	GLuint viewPosLoc;
	GLuint viewMatrixLoc;
	GLuint projectMatrixLoc;

	void loadShaders();
	void unloadShaders();

public:

	Scene(Scene const&)            = delete;
    void operator =(Scene const&)  = delete;

	void setup();
	void run(int, char**);

	void cleanup();
	void render();
	void initShaderVariableLocations();
	void setShaderVariables(const glm::vec4&);

	static Scene& getInstance();
};

void renderWrapper();
void cleanupWrapper();