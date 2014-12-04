#ifndef BEZIERPATCH_H_
#define BEZIERPATCH_H_

#include "Geode.h"
#include "Vector3d.h"
#include "Matrix4d.h"
#include "Material.h"


class BezierPatch : public Geode{
public :
	BezierPatch(Vector3d p0, Vector3d p1, Vector3d p2, Vector3d p3,
		Vector3d p4, Vector3d p5, Vector3d p6, Vector3d p7,
		Vector3d p8, Vector3d p9, Vector3d p10, Vector3d p11,
		Vector3d p12, Vector3d p13, Vector3d p14, Vector3d p15, int xx, int yy, Material *ma = NULL);
	BezierPatch(Vector3d *, int, int, Material *ma = NULL);
	Bs update();
	static const int v0[4];
	static const int v1[4];
	static const int v2[4];
	static const int v3[4];
	static const int u0[4];
	static const int u1[4];
	static const int u2[4];
	static const int u3[4];
	static Matrix4d m_bez;
	Vector3d getCp(int index);
	void setCp(int index, Vector3d cp);
	void sineWave(double h, double t);
private:
	// 16 control points, p0 is the bottom left corner, p3 is the bottom right corner, p12 is the top left corner, p15 is the top right corner
	Vector3d cp[16];
	void render();
	// resolution
	int x;
	int y;
	BezierPatch * bp;
	Material * m;
	Matrix4d gx, gy, gz;
	Matrix4d cx, cy, cz;
	Vector3d compute(double v, double u);
	Vector3d computeNormal(double v, double u);
	void setup();
};


#endif