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

	glClearColor(0.57f, 0.71f, 0.95f, 0.0f);
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
	shadowMatrixLoc = glGetUniformLocation(shadersId, "shadowMatrix");scaleMatrixLoc = glGetUniformLocation(shadersId, "scaleMatrix");
	translationMatrixLoc = glGetUniformLocation(shadersId, "translationMatrix");
}

void Scene::setShadowShaderVariables() {

	int drawShadow = 1;
	glUniform1i(drawShadowLoc, drawShadow);
  	glUniformMatrix4fv(shadowMatrixLoc, 1, GL_FALSE, &shadowMatrix[0][0]);
}

void Scene::setShaderVariables(Shape* shape) {

	// position variables
	glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE, &viewMatrix[0][0]);
	glUniformMatrix4fv(projectMatrixLoc, 1, GL_FALSE, &projectionMatrix[0][0]);

	// light variables
	glm::vec3 objectColor = shape->getColor();
	glUniform3f(objectColorLoc, objectColor[0], objectColor[1], objectColor[2]);
	glUniform3f(lightColorLoc, LightColor[0], LightColor[1], LightColor[2]);
	glUniform3f(lightPosLoc, LightPosition[0], LightPosition[1], LightPosition[2]);
	glUniform3f(viewPosLoc, EyePosition[0], EyePosition[1], EyePosition[2]);

	int drawShadow = 0;
	glUniform1i(drawShadowLoc, drawShadow);

	glm::mat4 scaleMatrix = shape->getScale();
	glUniformMatrix4fv(scaleMatrixLoc, 1, GL_FALSE, &scaleMatrix[0][0]);
	glm::mat4 translationMatrix = shape->getTranslation();
	glUniformMatrix4fv(translationMatrixLoc, 1, GL_FALSE, &translationMatrix[0][0]);
}

void Scene::drawTree(const glm::vec3& scale, const glm::vec3& translation) {
	Cylinder stump(scale * glm::vec3(0.1f, 0.1f, 0.275f), scale * (translation + glm::vec3(0.0f, 0.0f, 0.0f)));
	Sphere leaves(scale * glm::vec3(0.5f, 0.5f, 0.75f), scale * (translation + glm::vec3(0.0f, 0.0f, 1.75f)));
	stump.setColor(glm::vec4(0.396f, 0.262f, 0.129f, 0.5f));
	leaves.setColor(glm::vec4(0.1, 0.8f, 0.15f, 0.5f));
	drawObject(&stump);
	drawObject(&leaves);
}

void Scene::drawObject(Shape* shape) {

	glEnable(GL_DEPTH_TEST);
    setShaderVariables(shape);
    shape->Render();
    if (shape->getHasShadow()) {
        setShadowShaderVariables();
        shape->DrawShadow();
    }
}

void Scene::render() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	EyePosition[0] = ReferencePoint[0] + dist * cos(alpha) * cos(beta);
   	EyePosition[1] = ReferencePoint[1] + dist * cos(alpha) * sin(beta);
   	EyePosition[2] = ReferencePoint[2] + dist * sin(alpha);

	viewMatrix = glm::lookAt(EyePosition + position, ReferencePoint + position, glm::vec3(0.0f, 0.0f, 1.0f));
	projectionMatrix = glm::perspective(45.0f, GLfloat(windowWidth) / GLfloat(windowHeight), 0.1f, 50.0f);

	Ground ground(glm::vec3(100.0f, 100.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	ground.setColor(glm::vec4(0.05f, 0.67f, 0.16f, 1.0f));
	drawObject(&ground);

	Ground path(glm::vec3(100.0f, 0.25f, 0.0f), glm::vec3(0.0f, 0.0f, 0.01f));
	path.setColor(glm::vec4(1.0f, 0.8f, 0.7f, 1.0f));
	drawObject(&path);

	Cone piramid(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 2.0f), 4, 2);
	piramid.setColor(glm::vec4(0.05f, 0.67f, 0.16f, 1.0f));
	drawObject(&piramid);

	drawTree(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(3.0f, 4.0f, 0.0f));
	drawTree(glm::vec3(3.0f, 1.0f, 0.5f), glm::vec3(1.0f, 3.0f, 0.0f));
	drawTree(glm::vec3(1.0f, 2.0f, 3.0f), glm::vec3(-1.0f, -1.0f, 0.0f));

    glutSwapBuffers();
    glutPostRedisplay();
    glFlush();
}

void Scene::run(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
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
	case 'a':
		position.y -= 0.25;
		break;
	case 'd':
		position.y += 0.25;
		break;
	case 'w':
		position.x -= 0.25;
		break;
	case 's':
		position.x += 0.25;
		break;
	case 'q':
		position.z -= 0.25;
		break;
	case 'e':
		position.z += 0.25;
		break;
	if (key == 27)
		exit(0);
	}
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