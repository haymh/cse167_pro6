#ifndef PIECEWISEBEZIERPATCH_H_
#define PIECEWISEBEZIERPATCH_H_

#include "BezierPatch.h"
#include "Geode.h"
#include "Vector3d.h"


class PiecewiseBezierPatch : public Geode{
public :
	PiecewiseBezierPatch(int width, int height, int x, int y, Material * m = NULL);  // x,y are resolution
	Bs update();
	void setCP(int u, int v, Vector3d c);
	Vector3d getCP(int u, int v);
private:
	BezierPatch** vu;
	int w, h; // number of patches
	void render();

};

#endif