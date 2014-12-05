#include "BezierPatch.h"
#include "Material.h"
#include <iostream>

using namespace std;

const int BezierPatch::v0[4] = { 0, 1, 2, 3 };
const int BezierPatch::v1[4] = { 4, 5, 6, 7 };
const int BezierPatch::v2[4] = { 8, 9, 10, 11 };
const int BezierPatch::v3[4] = { 12, 13, 14, 15 };
const int BezierPatch::u0[4] = { 0, 4, 8, 12 };
const int BezierPatch::u1[4] = { 1, 5, 9, 13 };
const int BezierPatch::u2[4] = { 2, 6, 10, 14 };
const int BezierPatch::u3[4] = { 3, 7, 11, 15 };
Matrix4d BezierPatch::m_bez = Matrix4d(-1, 3, -3, 1,
										3, -6, 3, 0,
										-3, 3, 0, 0,
										1, 0, 0, 0);


BezierPatch::BezierPatch(Vector3d p0, Vector3d p1, Vector3d p2, Vector3d p3,
	Vector3d p4, Vector3d p5, Vector3d p6, Vector3d p7,
	Vector3d p8, Vector3d p9, Vector3d p10, Vector3d p11,
	Vector3d p12, Vector3d p13, Vector3d p14, Vector3d p15, int xx, int yy, Material *ma){
	cp[0] = p0;
	cp[1] = p1;
	cp[2] = p2;
	cp[3] = p3;
	cp[4] = p4;
	cp[5] = p5;
	cp[6] = p6;
	cp[7] = p7;
	cp[8] = p8;
	cp[9] = p9;
	cp[10] = p10;
	cp[11] = p11;
	cp[12] = p12;
	cp[13] = p13;
	cp[14] = p14;
	cp[15] = p15;
	x = xx;
	y = yy;
	m = ma;
	enableShader = false;
	setup();
	shader = new Shader("shaders/enviroment.vert", "shaders/environment.frag");
}

BezierPatch::BezierPatch(Vector3d * v, int xx, int yy, Material *ma){
	for (int i = 0; i < 16; i++){
		cp[i] = v[i];
	}
	x = xx;
	y = yy;
	m = ma;
	setup();
	shader = new Shader("shaders/enviroment.vert", "shaders/environment.frag");
}

void BezierPatch::setCp(int index, Vector3d c){
	cp[index] = c;
}

void BezierPatch::setup(){
	gx = Matrix4d(cp[0][0], cp[1][0], cp[2][0], cp[3][0],
		cp[4][0], cp[5][0], cp[6][0], cp[7][0],
		cp[8][0], cp[9][0], cp[10][0], cp[11][0],
		cp[12][0], cp[13][0], cp[14][0], cp[15][0]);
	gy = Matrix4d(cp[0][1], cp[1][1], cp[2][1], cp[3][1],
		cp[4][1], cp[5][1], cp[6][1], cp[7][1],
		cp[8][1], cp[9][1], cp[10][1], cp[11][1],
		cp[12][1], cp[13][1], cp[14][1], cp[15][1]);
	gz = Matrix4d(cp[0][2], cp[1][2], cp[2][2], cp[3][2],
		cp[4][2], cp[5][2], cp[6][2], cp[7][2],
		cp[8][2], cp[9][2], cp[10][2], cp[11][2],
		cp[12][2], cp[13][2], cp[14][2], cp[15][2]);
	cx = m_bez * gx * m_bez;
	cy = m_bez * gy * m_bez;
	cz = m_bez * gz * m_bez;

	
}

void BezierPatch::setSkyID(GLuint id){
	skyID = id;
}

void BezierPatch::useShader(bool b){
	enableShader = b;
}

void BezierPatch::sineWave(double h, double t){
	for (int i = 0; i < 16; i++){
		double x = cp[i][0];
		double z = cp[i][2];
		double d = sqrt(x * x + z * z);
		double y = h * sin(d * t * M_PI / 2);
		cp[i].set(1, y);
	}
	//cp[0].set(1, 0);
	//cp[3].set(1, 0);
	//cp[12].set(1, 0);
	//cp[15].set(1, 0);
	setup();
}

Bs BezierPatch::update(){
	return bs;
}

Vector3d BezierPatch::getCp(int index){
	return cp[index];
}

Vector3d BezierPatch::compute(double v, double u){
	double vv = v * v;
	double uu = u * u;
	Vector4d V(v * vv, vv, v, 1);
	Vector4d U(u * uu, uu, u, 1);
	double x = V * cx * U;
	double y = V * cy * U;
	double z = V * cz * U;
	return Vector3d(x, y, z);
}

Vector3d BezierPatch::computeNormal(double v, double u){
	double vv = v * v;
	double uu = u * u;
	Vector4d V(v * vv, vv, v, 1);
	Vector4d U(u * uu, uu, u, 1);
	Vector4d aV(3 * vv, 2 * v, 1, 0);
	Vector4d aU(3 * uu, 2 * u, 1, 0);

	double vx = U * cx * aV;
	double vy = U * cy * aV;
	double vz = U * cz * aV;
	Vector3d xv(vx, vy, vz);

	double ux = aU * cx * V;
	double uy = aU * cy * V;
	double uz = aU * cz * V;
	Vector3d xu(ux, uy, uz);

	return xu * xv;
}

void BezierPatch::render(){
	if (m != NULL){
		m->apply();
	}
	else
		glColor3d(1.0, 1.0, 1.0);
	double du = 1 / double(x);
	double dv = 1 / double(y);
	/*
	if (enableShader){
	shader->bind();
	glEnable(GL_TEXTURE_CUBE_MAP);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skyID);
	}
	for (int i = 0; i <= y - 1; i++){
		// figure out the two starting vertices
		
		Vector3d b = compute(i * dv, 0);
		Vector3d nb = computeNormal(i * dv, 0);
		nb.normalize();
		Vector3d a = compute((i + 1) * dv, 0);
		Vector3d na = computeNormal((i + 1) * dv, 0);
		na.normalize();
		
		glBegin(GL_TRIANGLE_STRIP);
		glNormal3d(na[0], na[1], na[2]);
		glVertex3d(a[0], a[1], a[2]);
		//cerr << "a: " << a[0] << ", " << a[1] << ", " << a[2] << endl;
		//cerr << "b: " << b[0] << ", " << b[1] << ", " << b[2] << endl;
		//system("pause");
		glNormal3d(nb[0], nb[1], nb[2]);
		glVertex3d(b[0], b[1], b[2]);
		// figure out the rest of points in ith row
		for (int j = 1; j <= x; j++){
			Vector3d c = compute((i + 1) * dv, j * du);
			Vector3d nc = computeNormal((i + 1) * dv, j * du);
			nc.normalize();
			Vector3d d = compute(i * dv, j * du);
			Vector3d nd = computeNormal(i * du, j * du);
			nd.normalize();
			//cerr << "c: " << c[0] << ", " << c[1] << ", " << c[2] << endl;
			//cerr << "d: " << d[0] << ", " << d[1] << ", " << d[2] << endl;
			glNormal3d(nc[0], nc[1], nc[2]);
			glVertex3d(c[0], c[1], c[2]);
			glNormal3d(nd[0], nd[1], nd[2]);
			glVertex3d(d[0], d[1], d[2]);
		}
		glEnd();
		if (enableShader){
		glDisable(GL_TEXTURE_CUBE_MAP);
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
		shader->unbind();
	}
		
	}
	*/
	///*
	if (enableShader){
		shader->bind();
		glEnable(GL_TEXTURE_CUBE_MAP);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, skyID);
	}
	glBegin(GL_QUADS);
	for (int i = 0; i <= y - 1; i++){
		Vector3d a = compute((i + 1) * dv, 0);
		Vector3d b = compute(i * dv, 0);
		Vector3d c, d;
		for (int j = 1; j <= x; j++){
			c = compute(i * dv, j * du);
			d = compute((i + 1) * dv, j * du);
			Vector3d v1 = b - a;
			Vector3d v2 = d - a;
			Vector3d n = v1 * v2;
			n.normalize();
			glNormal3d(n[0], n[1], n[2]);
			glVertex3d(a[0], a[1], a[2]);
			glVertex3d(b[0], b[1], b[2]);
			glVertex3d(c[0], c[1], c[2]);
			glVertex3d(d[0], d[1], d[2]);
			a = d;
			b = c;
		}
	}
	glEnd();
	if (enableShader){
		glDisable(GL_TEXTURE_CUBE_MAP);
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
		shader->unbind();
	}
	if (glGetError() != GL_NO_ERROR)
		cerr << "GL error" << endl;
	//*/
	

	//glBegin(GL_TRIANGLE_STRIP);
	//glVertex3d(0, 0, 0);
	//glVertex3d(1, 0, 4);
	//glVertex3d(-1, 3, 2);
	//glVertex3d(3, 2, 3);
	//glEnd();
}

