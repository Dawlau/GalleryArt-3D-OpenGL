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

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // black background
    loadShaders();
}

void Scene::render() {
	glClear(GL_COLOR_BUFFER_BIT);

	glm::mat4 viewMatrix = glm::lookAt(EyePosition, ReferencePoint, glm::vec3(0.0f, 0.0f, -100.0f));
	glUniformMatrix4fv(glGetUniformLocation(shadersId, "viewMatrix"), 1, GL_FALSE, &viewMatrix[0][0]);

	glm::mat4 projectionMatrix = glm::perspective(45.0f, GLfloat(windowWidth) / GLfloat(windowHeight), 1.0f, 50.0f);
	glUniformMatrix4fv(glGetUniformLocation(shadersId, "projectionMatrix"), 1, GL_FALSE, &projectionMatrix[0][0]);

	glUniformMatrix4fv(glGetUniformLocation(shadersId, "normMatrix"), 1, GL_FALSE, &normMatrix[0][0]);

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