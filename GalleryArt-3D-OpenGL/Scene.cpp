#include "Scene.h"
#include "loadShaders.h"
#include <iostream>
#include <iomanip>

Scene& Scene::getInstance() {

	static Scene instance;
	return instance;
}

void Scene::loadShaders() {

	shadersId = LoadShaders(vertexShaderPath, fragmentShaderPath);
  	glUseProgram(shadersId);
}

void Scene::unloadShaders() {

	glDeleteProgram(shadersId);
}

void Scene::cleanup() {

	unloadShaders();
}

void Scene::setup() {

	glClearColor(1.0f, 1.0f, 1.0f, 0.0f); // black background
    loadShaders();
	initShaderVariableLocations();
}

void Scene::initShaderVariableLocations() {

	projectMatrixLoc = glGetUniformLocation(shadersId, "projectionMatrix");
	viewMatrixLoc = glGetUniformLocation(shadersId, "viewMatrix");
	objectColorLoc = glGetUniformLocation(shadersId, "objectColor");
	lightColorLoc = glGetUniformLocation(shadersId, "lightColor");
	lightPosLoc = glGetUniformLocation(shadersId, "lightPos");
	viewPosLoc = glGetUniformLocation(shadersId, "viewPos");
}

void Scene::setShaderVariables(const glm::vec4& objectColor) {

	glm::mat4 viewMatrix = glm::lookAt(EyePosition, ReferencePoint, glm::vec3(0.0f, 0.0f, 1.0f));
	glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE, &viewMatrix[0][0]);

	glm::mat4 projectionMatrix = glm::perspective(45.0f, GLfloat(windowWidth) / GLfloat(windowHeight), 1.0f, 50.0f);
	glUniformMatrix4fv(projectMatrixLoc, 1, GL_FALSE, &projectionMatrix[0][0]);

	glUniform3f(objectColorLoc, objectColor[0], objectColor[1], objectColor[2]);
	glUniform3f(lightColorLoc, 1.0f, 1.0f, 1.0f);
	glUniform3f(lightPosLoc, 0.f, 0.f, 50.f);
	glUniform3f(viewPosLoc, EyePosition[0], EyePosition[1], EyePosition[2]);
}

void Scene::render() {
	glClear(GL_COLOR_BUFFER_BIT);

	setShaderVariables(ground.getColor());
	ground.Render();
	cylinder.Render();

    glutSwapBuffers();
    glutPostRedisplay();
    glFlush();
}

void Scene::run(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(initialWindowsPosX, initialWindowsPosY);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("Art Gallery");

	glewInit();
	setup();

	glutDisplayFunc(renderWrapper);
	glutCloseFunc(cleanupWrapper);

	glutMainLoop();
}

void renderWrapper() {

	Scene::getInstance().render();
}

void cleanupWrapper() {

	Scene::getInstance().cleanup();
}