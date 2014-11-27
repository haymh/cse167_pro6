#ifndef _VECTOR4_H_
#define _VECTOR4_H_

#include "GL/glut.h"
#include "Vector3d.h"

class Vector4d
{
protected:
	GLdouble v[4];   // matrix elements

public:
	Vector4d();        // constructor
	Vector4d(GLdouble, GLdouble, GLdouble);
	Vector4d(GLdouble, GLdouble, GLdouble, GLdouble);
	void set(int index, GLdouble value);
	GLdouble get(int index);
	Vector4d& operator=(Vector4d&);
	GLdouble operator[](int index);
	Vector4d operator+(Vector4d & another);
	void add(Vector4d & another);
	Vector4d operator-(Vector4d & another);
	Vector3d getVector3d();
	void substract(Vector4d & another);
	void dehomogenize(); 
	void print();

};

#endif