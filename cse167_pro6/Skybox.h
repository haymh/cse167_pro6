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
	GLuint getSkyID();

private :
	bool facePresent[6];
	GLuint faceID[6];
	GLuint skyID;
	double D;
	bool load_cube_map_side(GLuint texture, GLenum side_target, const char* file_name);
	void create_cube_map(const char* front,const char* back,const char* top,const char* bottom,const char* left,const char* right,GLuint* tex_cube);
	void init();
	void init2();
	void init3();
	void render();
	void render1();
	void render2();
	void render3();
	void render4();
	void render5();
	Shader *shader[5];
	Shader *skyShader;
	GLuint vao;
	GLuint SkyBoxVBO;
};

#endif