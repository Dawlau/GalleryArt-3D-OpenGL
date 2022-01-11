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
	drawShadowLoc = glGetUniformLocation(shadersId, "drawShadow");
	shadowMatrixLoc = glGetUniformLocation(shadersId, "shadowMatrix");
}

void Scene::setShadowShaderVariables() {

	int drawShadow = 1;
	glUniform1i(drawShadowLoc, drawShadow);
  	glUniformMatrix4fv(shadowMatrixLoc, 1, GL_FALSE, &shadowMatrix[0][0]);
  	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, (void*)(6));
}

void Scene::setShaderVariables(const glm::vec4& objectColor) {

	// position variables
	glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE, &viewMatrix[0][0]);
	glUniformMatrix4fv(projectMatrixLoc, 1, GL_FALSE, &projectionMatrix[0][0]);

	// light variables
	glUniform3f(objectColorLoc, objectColor[0], objectColor[1], objectColor[2]);
	glUniform3f(lightColorLoc, LightColor[0], LightColor[1], LightColor[2]);
	glUniform3f(lightPosLoc, LightPosition[0], LightPosition[1], LightPosition[2]);
	glUniform3f(viewPosLoc, EyePosition[0], EyePosition[1], EyePosition[2]);

	int drawShadow = 0;
	glUniform1i(drawShadowLoc, drawShadow);
}

void Scene::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	EyePosition[0] = ReferencePoint[0] + dist * cos(alpha) * cos(beta);
   	EyePosition[1] = ReferencePoint[1] + dist * cos(alpha) * sin(beta);
   	EyePosition[2] = ReferencePoint[2] + dist * sin(alpha);

	viewMatrix = glm::lookAt(EyePosition, ReferencePoint, glm::vec3(0.0f, 0.0f, 1.0f));
	projectionMatrix = glm::perspective(45.0f, GLfloat(windowWidth) / GLfloat(windowHeight), 1.0f, 50.0f);

	setShaderVariables(ground.getColor());
	ground.Render();

	setShaderVariables(cube.getColor());
	cube.Render();
	if (cube.getHasShadow()){
		setShadowShaderVariables();
		cube.DrawShadow();
	}

	/*setShaderVariables(cylinder.getColor());
	cylinder.Render();
	if (cylinder.getHasShadow()){
		setShadowShaderVariables();
		cylinder.DrawShadow();
	}*/

	/*setShaderVariables(sphere.getColor());
	sphere.Render();
	if (sphere.getHasShadow()) {
		setShadowShaderVariables();
		sphere.DrawShadow();
	}*/

	/*setShaderVariables(cone.getColor());
	cone.Render();
	if (cone.getHasShadow()) {
		setShadowShaderVariables();
		cone.DrawShadow();
	}*/

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
	glutKeyboardFunc(processNormalKeysWrapper);
	glutSpecialFunc(processSpecialKeysWrapper);
	glutCloseFunc(cleanupWrapper);

	glutMainLoop();
}

void Scene::processSpecialKeys(int key, int xx, int yy) {

	switch (key) {
		case GLUT_KEY_LEFT :
			beta -= 0.01;
			break;
		case GLUT_KEY_RIGHT :
			beta += 0.01;
			break;
		case GLUT_KEY_UP :
			alpha += 0.01;
			break;
		case GLUT_KEY_DOWN :
			alpha -= 0.01;
			break;
	}
}

void Scene::processNormalKeys(unsigned char key, int x, int y)
{
	switch (key) {
	case '-':
		dist -= 0.5;
		break;
	case '+':
		dist += 0.5;
		break;
	}
	if (key == 27)
		exit(0);
}

void renderWrapper() {

	Scene::getInstance().render();
}

void cleanupWrapper() {

	Scene::getInstance().cleanup();
}

void processSpecialKeysWrapper(int key, int xx, int yy) {

	Scene::getInstance().processSpecialKeys(key, xx, yy);
}

void processNormalKeysWrapper(unsigned char key, int xx, int yy) {

	Scene::getInstance().processNormalKeys(key, xx, yy);
}