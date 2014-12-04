#include "PiecewiseBezierPatch.h"

PiecewiseBezierPatch::PiecewiseBezierPatch(int width, int height, int x, int y, Material * m){
	w = width;
	h = height;
	vu = new BezierPatch* [h*w];
	Vector3d cp[16];
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			cp[i * 4 + j] = Vector3d(i * 4 + j, 0, i);

	for (int i = 0; i < h; i++){
		for (int j = 0; j < w; j++){
			vu[i * h + j] = new BezierPatch(cp, x, y, m);
			// update x value
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					cp[i * 4 + j].set(0, cp[i * 4 + j][0] + 3);
		}
		// reset x value
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				cp[i * 4 + j].set(0, i * 4 + j);
		// update z value
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				cp[j * 4 + i].set(2, cp[j * 4 + i][2] + 3);
	}

}

Bs PiecewiseBezierPatch::update(){
	return bs;
}

void PiecewiseBezierPatch::setCP(int u, int v, Vector3d c){
	if (u < 0 || u > 3 * w || v < 0 || v > 3 * h)
		return;
	int x = u / 3
}

void PiecewiseBezierPatch::render(){

}