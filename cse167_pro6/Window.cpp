#include <stdlib.h>
#include "shader.h"
#include "Window.h"
#include <iostream>
#include "Matrix4d.h"

#include "Debug.h"
#include "Const.h"
#include "Light.h"
#include "Material.h"
#include "ObjNode.h"
#include "Cone.h"
#include "MatrixTransform.h"
#include "Sphere.h"
#include "Skybox.h"




#define ROTSCALE 180.0;
#define ZOOMSCALE 2.0;
#define TIME_INTERVAL 0.001;
#define WAVE_HEIGHT 3.0;

using namespace std;



int Window::width  = 512;   // set window width in pixels here
int Window::height = 512;   // set window height in pixels here
int Window::old_x = width / 2;
int Window::old_y = height / 2;

MatrixTransform * Window::root = new MatrixTransform(Matrix4d());
MatrixTransform * Window::ocean;
BezierPatch * Window::bp;

bool useShader;

//trackball variables
control::MOVEMENT movement = control::NONE;
Vector3d lastPoint;
Matrix4d rotation;
Matrix4d scaling;
MatrixTransform* Window::scaling_mt;
MatrixTransform* Window::rotate_mt;

// camera parameters
Vector3d eye(0, 0, 1);
Vector3d lookat(0, 0, 0);
Vector3d up(0, 1, 0);

Camera cam(eye,lookat, up);


// spotlight sources parameters
f4 ambient(0.1, 0.1, 0.1, 1.0);
f4 diffuse(0.2, 0.2, 0.2, 1.0);
f4 specular(1, 1, 1, 1.0);
f4 position(3.0, 10.0, 0.0, 1.0);
f3 spot_direction(-3.0, -10.0, 0.0);

// point light source parameters
f4 p_ambient(0.4, 0.4, 0.4, 1.0);
f4 p_diffuse(1, 1, 1, 1.0);
f4 position2(0.0, 5.0, -4.0, 0.0);

Light spotLight(ambient, diffuse, specular, position);
Light pointLight(p_ambient, p_diffuse, specular, position2);

//shine material parameters
f4 m_ambient(0.328125, 0.7421875, 0.90625, 0.267);
f4 m_diffuse(0.50754, 0.50754, 0.50754, 1.0);
f4 m_specular(0.508273, 0.508273, 0.508273, 1.0);
f4 m_emission(0.8, 0.8, 0.8, 0.0);
float shininess = 51.2;

Material material;
Material material_cp;

Shader * shader;

KEY key = F1;
Vector3d cp[16];

double time = 0.0;

void Window::init(){
	useShader = false;
	Matrix4d t;
	t.makeTranslate(0, -13, 0);
	ocean = new MatrixTransform(t);
	material.setAmbient(m_ambient);
	material.setDiffuse(m_diffuse);
	material.setSpecular(m_specular);
	material.setShininess(shininess);

	material_cp.setAmbient(f4(1.0, 0.0, 0.0, 1.0));
	material_cp.setDiffuse(m_diffuse);
	
	cp[0] = Vector3d(-20, 0, 20);	cp[1] = Vector3d(-7, -3, 20);	cp[2] = Vector3d(7, -4, 20);	cp[3] = Vector3d(20, 0, 20);
	cp[4] = Vector3d(-20, -2, 7);	cp[5] = Vector3d(-7, 0, 7);		cp[6] = Vector3d(7, -2, 7);		cp[7] = Vector3d(20, -1, 7);
	cp[8] = Vector3d(-20, -4, -7);	cp[9] = Vector3d(-7, -2, -7);	cp[10] = Vector3d(7, -3, -7);	cp[11] = Vector3d(20, -2, -7);
	cp[12] = Vector3d(-20, 0, -20);	cp[13] = Vector3d(-7, -2, -20);	cp[14] = Vector3d(7, -2, -20);	cp[15] = Vector3d(20, 0, -20);

	scaling_mt = new MatrixTransform(Matrix4d());
	rotate_mt = new MatrixTransform(Matrix4d());
	bp = new BezierPatch(cp, 150, 150, &material);
	ocean->addChild(bp);
	root->addChild(rotate_mt);
	rotate_mt->addChild(scaling_mt);
	scaling_mt->addChild(ocean);

	MatrixTransform *cp_mt = new MatrixTransform(Matrix4d());
	for (int i = 0; i < 16; i++){
		t.makeTranslate(cp[i][0], cp[i][1], cp[i][2]);
		MatrixTransform *mt = new MatrixTransform(t);
		mt->addChild(new Sphere(0.5, 20, 20, Vector3d(1, 0, 0), draw::SOLID, &material_cp));
		cp_mt->addChild(mt);
	}
	ocean->addChild(cp_mt);

	//loading texture
	Skybox * skybox = new Skybox(20);
	scaling_mt->addChild(skybox);

	bp->setSkyID(skybox->getSkyID());
	bp->useShader(false);
}


//----------------------------------------------------------------------------
// Callback method called when system is idle.
void Window::idleCallback()
{
	
	displayCallback();         // call display routine to show the cube
	double h = WAVE_HEIGHT;
	bp->sineWave(h, time);
	time += TIME_INTERVAL;
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when graphics window is resized by the user
void Window::reshapeCallback(int w, int h)
{
	cerr << "Window::reshapeCallback called" << endl;
	width = w;
	height = h;
	glViewport(0, 0, w, h);  // set new viewport size
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, double(width) / (double)height, 1.0, 1000.0); // set perspective projection viewing frustum
	//gluLookAt(eye[0], eye[1], eye[2], lookat[0], lookat[1], lookat[2], up[0], up[1], up[2]);
	//glMatrixMode(GL_MODELVIEW);
	//glLoadMatrixd(cam.getMatrix().getPointer());
	//spotLight.apply();
	//pointLight.apply();
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when window readraw is necessary or when glutPostRedisplay() was called.
void Window::displayCallback()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glLoadMatrixd(cam.getMatrix().getPointer());
	//spotLight.apply();
	pointLight.apply();
	glMatrixMode(GL_MODELVIEW);
	
	//root->draw(cam.getMatrix());
	root->draw(cam.getMatrix());
	
	glFlush();
	glutSwapBuffers(); 
}


void Window::keyboardProcess(unsigned char key, int x, int y){
	switch (key){
	case 'e':
		useShader = !useShader;
		bp->useShader(useShader);
		break;
	case 27:
		exit(0);
	}
}
void Window::processSpecialKeys(int k, int x, int y){
	
}
void Window::mouseMotionProcess(int x, int y){
	Vector3d direction;
	double pixel_diff;
	double rot_angle, zoom_factor;
	Vector3d curPoint;
	curPoint = trackBallMapping(x, y);
	switch (movement){
	case control::ROTATION:
	{
		direction = curPoint - lastPoint;
		double velocity = direction.magnitude();
		if (velocity > 0.0001){
			Vector3d rotAxis = lastPoint * curPoint;
			rotAxis.normalize();
			rot_angle = velocity * ROTSCALE;
			Matrix4d r;
			r.makeRotate(rot_angle, rotAxis);
			rotation = r * rotation;
			rotate_mt->setMatrix(rotation);
		}
	}
		break;
	case control::SCALING:
	{
		pixel_diff = curPoint[1] - lastPoint[1];
		zoom_factor = 1.0 + pixel_diff * ZOOMSCALE;
		Matrix4d s;
		s.makeScale(zoom_factor, zoom_factor, zoom_factor);
		scaling = scaling * s;
		scaling_mt->setMatrix(scaling);
		displayCallback();

	}
		break;
	}
	lastPoint = curPoint;
}


void Window::mouseProcess(int button, int state, int x, int y){
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		movement = control::ROTATION;
		old_x = x;
		old_y = y;
		lastPoint = trackBallMapping(x, y);
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
		movement = control::SCALING;
		old_x = x;
		old_y = y;
		lastPoint = trackBallMapping(x, y);
	}
	else
		movement = control::NONE;
}


Vector3d Window::trackBallMapping(int x, int y){
	Vector3d v(double (2*x - width) / double (width), double (height - 2*y) / double (height), 0);
	double d = v.magnitude();
	d = d < 1.0 ? d : 1.0;
	v.set(2, sqrt(1.001 - d*d));
	v.normalize();
	return v;
}