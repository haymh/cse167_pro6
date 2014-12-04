#ifndef SKYBOX_H_
#define SKYBOX_H_

#include "Geode.h"
#include "shader.h"

enum face { FRONT, BACK, LEFT, RIGHT, TOP, BOTTOM };

class Skybox : public Geode{
public:
	Skybox(double radius);
	void loadFace(face f, char* filename);
	void loadSkybox(const char* front,
					const char* back,
					const char* top,
					const char* bottom,
					const char* left,
					const char* right);
	Bs update();

private :
	bool facePresent[6];
	GLuint faceID[6];
	GLuint skyID;
	double D;
	void render();
	void render1();
	void render2();
	void render3();
	Shader *shader;
	GLuint vao;
};

#endif