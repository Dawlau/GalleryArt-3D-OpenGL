#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
#include "glmInclude.h"
#include "Ground.h"
#include "Cylinder.h"
#include "Cone.h"
#include "Cube.h"
#include "Sphere.h"

float getRandom(const float&, const float&);
bool getRandomBool();

class Scene {

private:

	Scene() {
		float D = 0.02f;
		shadowMatrix = glm::mat4(
			 //LightPosition[2] + 0.5f, 0, -LightPosition[0], -0.5f * LightPosition[0],
			 //0, LightPosition[2] + 0.5f, -LightPosition[1], -0.5f * LightPosition[1],
			 //0, 0, 0.5f, -0.5f * LightPosition[2],
			 //0, 0, -1, LightPosition[2]
			// LightPosition[2], 0, -LightPosition[0], 0,
			// 0, LightPosition[2] + 0.5f, -LightPosition[1], 0,
			// 0, 0, 0, 0,
			// 0, 0, -1, LightPosition[2]
			LightPosition[2] + D, 0, 0, 0,
			0, LightPosition[2] + D, 0, 0,
			-LightPosition[0], -LightPosition[1], D, -1,
			-LightPosition[0] * D, -LightPosition[1] * D, LightPosition[2] * D, LightPosition[2]
		);

		treeTransformations.reserve(treesCount);
		for(int i = 0; i < treesCount; i++) {
			glm::vec3 scale = glm::vec3(getRandom(1.0f, 3.0f), getRandom(1.0f, 3.0f), getRandom(1.0f, 2.0f));
			glm::vec3 translation;

			bool side = getRandomBool();
			if(side) { // right
				translation = glm::vec3(getRandom(-20.0f, 20.0f), getRandom(2.0f, 20.0f), 0.0f);
			}
			else {
				translation = glm::vec3(getRandom(-20.0f, 20.0f), getRandom(-20.0f, -2.0f), 0.0f);
			}

			treeTransformations.push_back({scale, translation});
		}
	}
	Cylinder cylinder;
	Cone cone;
	Sphere sphere;
	Cube cube;

	const int treesCount = 500;
	std::vector < std::pair <glm::vec3, glm::vec3> > treeTransformations;

	static constexpr float PI = 3.141592f;

	static const int initialWindowsPosX = 100;
	static const int initialWindowsPosY = 100;

	static const int windowWidth = 800;
	static const int windowHeight = 600;

	const glm::vec3 LightPosition = glm::vec3(100.0f, -50.0f, 100.0f);
	const glm::vec3 LightColor = glm::vec3(1.0f, 1.0f, 1.0f);

	glm::vec3 EyePosition = glm::vec3(0.0f, -10.5f, 1.0f);
	glm::vec3 ReferencePoint = glm::vec3(0.0f, 0.0f, 0.0f);

	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;
	glm::mat4 shadowMatrix;

	const char* vertexShaderPath = "Shader.vert";
	const char* fragmentShaderPath = "Shader.frag";

	GLuint shadersId;
	GLuint objectColorLoc;
	GLuint lightColorLoc;
	GLuint lightPosLoc;
	GLuint viewPosLoc;
	GLuint viewMatrixLoc;
	GLuint projectMatrixLoc;
	GLuint drawShadowLoc;
	GLuint shadowMatrixLoc;
	GLuint scaleMatrixLoc;
	GLuint translationMatrixLoc;

	float alpha = PI / 8;
	float beta = 0.0f;
	float dist = 10.0f;
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);

	void loadShaders();
	void unloadShaders();

public:

	Scene(Scene const&)            = delete;
    void operator =(Scene const&)  = delete;

	void setup();
	void run(int, char**);

	void cleanup();
	void render();
	void processSpecialKeys(int, int, int);
	void processNormalKeys(unsigned char, int, int);

	void initShaderVariableLocations();
	void setShaderVariables(Shape*);
	void setShadowShaderVariables();
	void drawTree(const glm::vec3& scale, const glm::vec3& translation);

	void drawObject(Shape*);

	static Scene& getInstance();
};

void renderWrapper();
void cleanupWrapper();
void processSpecialKeysWrapper(int, int, int);
void processNormalKeysWrapper(unsigned char, int, int);