#include <iostream>
#include "Window.h"
using namespace std;
int main(int argc, char** argv){
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(Window::width, Window::height);
	glutCreateWindow("project 5");

	glEnable(GL_DEPTH_TEST);            	      // enable depth buffering
	glClear(GL_DEPTH_BUFFER_BIT);       	      // clear depth buffer
	glClearColor(0.0, 0.0, 0.0, 0.0);   	      // set clear color to black
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  // set polygon drawing mode to fill front and back of each polygon
	glEnable(GL_CULL_FACE);     // disable backface culling to render both sides of polygons
	glShadeModel(GL_SMOOTH);             	      // set shading to smooth
	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

	Window::init();
	glutReshapeFunc(Window::reshapeCallback);
	glutDisplayFunc(Window::displayCallback);
	glutKeyboardFunc(Window::keyboardProcess);
	glutIdleFunc(Window::idleCallback);
	glutMouseFunc(Window::mouseProcess);
	glutMotionFunc(Window::mouseMotionProcess);
	//glutPassiveMotionFunc(Window::mousePassiveMotionProcess);
	glutSpecialFunc(Window::processSpecialKeys);
	glutMainLoop();
}