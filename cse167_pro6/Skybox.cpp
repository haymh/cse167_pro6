#include "glee.h"
#include "Skybox.h"
#include "Texture.h"
#include "stb_image.h"
#include <iostream>

char* _front = "texture/nissiBeach/negz.jpg";
char* _back = "texture/nissiBeach/posz.jpg";
char* _left = "texture/nissiBeach/negx.jpg";
char* _right = "texture/nissiBeach/posx.jpg";
char* _top = "texture/nissiBeach/posy.jpg";
char* _bottom = "texture/nissiBeach/negy.jpg";

using namespace std;

Skybox::Skybox(double radius){
	D = radius;
	for (int i = 0; i < 6; i++){
		facePresent[i] = false;
	}
	bs.center = Vector3d(0, 0, 0);
	bs.radius = sqrt(D * D * 2);
	/*
	float points[] = {
		-10.0f, 10.0f, -10.0f,
		-10.0f, -10.0f, -10.0f,
		10.0f, -10.0f, -10.0f,
		10.0f, -10.0f, -10.0f,
		10.0f, 10.0f, -10.0f,
		-10.0f, 10.0f, -10.0f,

		-10.0f, -10.0f, 10.0f,
		-10.0f, -10.0f, -10.0f,
		-10.0f, 10.0f, -10.0f,
		-10.0f, 10.0f, -10.0f,
		-10.0f, 10.0f, 10.0f,
		-10.0f, -10.0f, 10.0f,

		10.0f, -10.0f, -10.0f,
		10.0f, -10.0f, 10.0f,
		10.0f, 10.0f, 10.0f,
		10.0f, 10.0f, 10.0f,
		10.0f, 10.0f, -10.0f,
		10.0f, -10.0f, -10.0f,

		-10.0f, -10.0f, 10.0f,
		-10.0f, 10.0f, 10.0f,
		10.0f, 10.0f, 10.0f,
		10.0f, 10.0f, 10.0f,
		10.0f, -10.0f, 10.0f,
		-10.0f, -10.0f, 10.0f,

		-10.0f, 10.0f, -10.0f,
		10.0f, 10.0f, -10.0f,
		10.0f, 10.0f, 10.0f,
		10.0f, 10.0f, 10.0f,
		-10.0f, 10.0f, 10.0f,
		-10.0f, 10.0f, -10.0f,

		-10.0f, -10.0f, -10.0f,
		-10.0f, -10.0f, 10.0f,
		10.0f, -10.0f, -10.0f,
		10.0f, -10.0f, -10.0f,
		-10.0f, -10.0f, 10.0f,
		10.0f, -10.0f, 10.0f
	};
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(
		GL_ARRAY_BUFFER, 3 * 36 * sizeof(GLfloat), &points, GL_STATIC_DRAW);


	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	shader = new Shader("shaders/skybox.vert", "shaders/skybox.frag");
	*/
	//init();
	float SkyBoxVertices[] =
	{	// x, y, z, x, y, z, x, y, z, x, y, z
		1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f, // +X
		-1.0f, -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, // -X
		-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, // +Y
		-1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, // -Y
		1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, // +Z
		-1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f  // -Z
	};
	glGenBuffers(1, &SkyBoxVBO);
	glBindBuffer(GL_ARRAY_BUFFER, SkyBoxVBO);
	glBufferData(GL_ARRAY_BUFFER, 288, SkyBoxVertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	init3();
	
}
/*
void Skybox::init(){
	
	
	//shader[TOP] = new Shader("shaders/top.vert", "shaders/top.frag");
	//shader[LEFT] = new Shader("shaders/left.vert", "shaders/left.frag");
	//shader[RIGHT] = new Shader("shaders/right.vert", "shaders/right.frag");

	int w, h;
	unsigned char* image;
	
	glGenTextures(6, &faceID[0]);
	if (faceID[FRONT] == faceID[BACK])
		cerr << "shit" << endl;
	GLuint e = glGetError();
	if (e != GL_NO_ERROR)
		cerr << " gl error 1: " << e << endl;

	//glActiveTexture(GL_TEXTURE0);
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, faceID[FRONT]);
	shader[FRONT] = new Shader("shaders/front.vert", "shaders/front.frag");
	image = SOIL_load_image("texture/deck/front.jpg", &w, &h, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glUniform1i(glGetUniformLocation(shader[FRONT]->getPid(), "FrontMap"), 0);
	SOIL_free_image_data(image);
	glDisable(GL_TEXTURE_2D);

	
	//glActiveTexture(GL_TEXTURE1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, faceID[BACK]);
	shader[BACK] = new Shader("shaders/back.vert", "shaders/back.frag");
	image = SOIL_load_image("texture/deck/back.jpg", &w, &h, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glUniform1i(glGetUniformLocation(shader[BACK]->getPid(), "BackMap"), 0);
	glDisable(GL_TEXTURE_2D);

	

	

	
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, faceID[TOP]);
	image = SOIL_load_image("texture/deck/top.jpg", &w, &h, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB,
	GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);

	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, faceID[LEFT]);
	image = SOIL_load_image("texture/deck/left.jpg", &w, &h, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB,
	GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);

	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, faceID[RIGHT]);
	image = SOIL_load_image("texture/deck/right.jpg", &w, &h, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB,
	GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	

	
	
	//glUniform1i(glGetUniformLocation(shader[TOP]->getPid(), "TopMap"), 2);
	//glUniform1i(glGetUniformLocation(shader[LEFT]->getPid(), "LeftMap"), 3);
	//glUniform1i(glGetUniformLocation(shader[RIGHT]->getPid(), "RightMap"), 4);
	if (e != GL_NO_ERROR){
		cerr << " gl error 5: " << e << endl;
		cerr << gluErrorString(e);
	}
	// Make sure no bytes are padded:
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	
	// Select GL_MODULATE to mix texture with polygon color for shading:
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// Use bilinear interpolation:
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	e = glGetError();
	
		
}
*/
void Skybox::init(){}

GLuint Skybox::getSkyID(){
	return skyID;
}

bool Skybox::load_cube_map_side(GLuint texture, GLenum side_target, const char* file_name) {
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

	int x, y, n;
	int force_channels = 4;
	unsigned char*  image_data = stbi_load(
		file_name, &x, &y, &n, force_channels);
	if (!image_data) {
		fprintf(stderr, "ERROR: could not load %s\n", file_name);
		return false;
	}
	// non-power-of-2 dimensions check
	if ((x & (x - 1)) != 0 || (y & (y - 1)) != 0) {
		fprintf(
			stderr, "WARNING: image %s is not power-of-2 dimensions\n", file_name
			);
	}

	// copy image data into 'target' side of cube map
	glTexImage2D(
		side_target,
		0,
		GL_RGBA,
		x,
		y,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		image_data
		);
	free(image_data);
	return true;
}

void Skybox::create_cube_map(const char* front,const char* back,const char* top,const char* bottom,const char* left,const char* right,GLuint* tex_cube) {
	// generate a cube-map texture to hold all the sides
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, tex_cube);

	// load each image and copy into a side of the cube-map texture
	if (!load_cube_map_side(*tex_cube, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, front))
		cerr << front << " doesn't load" << endl;
	if (!load_cube_map_side(*tex_cube, GL_TEXTURE_CUBE_MAP_POSITIVE_Z, back))
		cerr << back << " doesn't load" << endl;
	if(!load_cube_map_side(*tex_cube, GL_TEXTURE_CUBE_MAP_POSITIVE_Y, top))
		cerr << top << " doesn't load" << endl;
	if(!load_cube_map_side(*tex_cube, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, bottom))
		cerr << bottom << " doesn't load" << endl;
	if(!load_cube_map_side(*tex_cube, GL_TEXTURE_CUBE_MAP_NEGATIVE_X, left))
		cerr << left << " doesn't load" << endl;
	if(!load_cube_map_side(*tex_cube, GL_TEXTURE_CUBE_MAP_POSITIVE_X, right))
		cerr << right << " doesn't load" << endl;
	// format cube map texture
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}


/*
void Skybox::init2(){
	glEnable(GL_TEXTURE_CUBE_MAP);
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &skyID);
	int w, h;
	unsigned char* image;
	image = SOIL_load_image("texture/deck/front.jpg", &w, &h, 0, SOIL_LOAD_RGB);
	system("pause");
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	system("pause");
	SOIL_free_image_data(image);
	system("pause");
	GLuint e = glGetError();
	if (e != GL_NO_ERROR)
		cerr << " gl error 1: " << e << endl;

	image = SOIL_load_image("texture/deck/back.jpg", &w, &h, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);

	image = SOIL_load_image("texture/deck/right.jpg", &w, &h, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	
	image = SOIL_load_image("texture/deck/left.jpg", &w, &h, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);

	image = SOIL_load_image("texture/deck/top.jpg", &w, &h, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);

	image = SOIL_load_image("texture/deck/bottom.jpg", &w, &h, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	/*
	skyID = SOIL_load_OGL_cubemap
		(
		"texture/deck/right.jpg",
		"texture/deck/left.jpg",
		"texture/deck/top.jpg",
		"texture/deck/bottom.jpg",
		"texture/deck/front.jpg",
		"texture/deck/back.jpg",
		SOIL_LOAD_RGB,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS
		);
	
	
	e = glGetError();
	if (e != GL_NO_ERROR)
		cerr << " gl error 2: " << e << endl;
	glBindTexture(GL_TEXTURE_CUBE_MAP, skyID);
	e = glGetError();
	if (e != GL_NO_ERROR)
		cerr << " gl error 3: " << e << endl;
	skyShader = new Shader("shaders/skybox.vert", "shaders/skybox.frag");
	//glUniform1i(glGetUniformLocation(skyShader->getPid(), "CubeMap"), 0);
	e = glGetError();
	if (e != GL_NO_ERROR)
		cerr << " gl error 4: " << e << endl;

}
*/

void Skybox::init2(){
}

void Skybox::init3(){
	glEnable(GL_TEXTURE_CUBE_MAP);
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &skyID);
	create_cube_map(_front, _back, _top, _bottom, _left, _right, &skyID);
	skyShader = new Shader("shaders/skybox.vert", "shaders/skybox.frag");

}

void Skybox::loadFace(face f, char* filename){
	GLuint id = Texture::loadTexBMP(filename);
	facePresent[f] = true;
	faceID[f] = id;
}

void Skybox::loadSkybox(const char* front,const char* back,const char* top,const char* bottom,const char* left,const char* right){
	GLuint texture;
	glEnable(GL_TEXTURE_CUBE_MAP);
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &texture);
	if (front != NULL){
		Texture::loadSideBMP(texture, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, front);
		facePresent[FRONT] = true;
	}
	if (back != NULL){
		Texture::loadSideBMP(texture, GL_TEXTURE_CUBE_MAP_POSITIVE_Z, back);
		facePresent[BACK] = true;
	}
	if (top != NULL){
		Texture::loadSideBMP(texture, GL_TEXTURE_CUBE_MAP_POSITIVE_Y, top);
		facePresent[TOP] = true;
	}
	if (bottom != NULL){
		Texture::loadSideBMP(texture, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, bottom);
		facePresent[BOTTOM] = true;
	}
	if (left != NULL){
		Texture::loadSideBMP(texture, GL_TEXTURE_CUBE_MAP_NEGATIVE_X, left);
		facePresent[LEFT] = true;
	}
	if (right != NULL){
		Texture::loadSideBMP(texture, GL_TEXTURE_CUBE_MAP_POSITIVE_X, right);
		facePresent[RIGHT] = true;
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	skyID = texture;
	
}

Bs Skybox::update(){
	return bs;
}

void Skybox::render1(){
	glDisable(GL_LIGHTING);
	//glDisable(GL_DEPTH_TEST);	// skybox should be drawn behind anything else
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_TEXTURE_2D);

	/* Sides */
	//shader->bind();

	if (facePresent[FRONT]){
		//glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, faceID[FRONT]);
		glBegin(GL_QUADS);
		//glBindTexture(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, skyID);
		glTexCoord2f(0, 0); glVertex3f(+D, -D, -D);
		glTexCoord2f(1, 0); glVertex3f(+D, -D, +D);
		glTexCoord2f(1, 1); glVertex3f(+D, +D, +D);
		glTexCoord2f(0, 1); glVertex3f(+D, +D, -D);
		glEnd();
	}

	if (facePresent[BACK]){
		//glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, faceID[BACK]);
		glBegin(GL_QUADS);
		//glBindTexture(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, skyID);
		glTexCoord2f(0, 0); glVertex3f(-D, -D, +D);
		glTexCoord2f(1, 0); glVertex3f(-D, -D, -D);
		glTexCoord2f(1, 1); glVertex3f(-D, +D, -D);
		glTexCoord2f(0, 1); glVertex3f(-D, +D, +D);
		glEnd();
	}

	if (facePresent[LEFT]){
		//glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, faceID[LEFT]);
		glBegin(GL_QUADS);
		//glBindTexture(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, skyID);
		glTexCoord2f(0, 0); glVertex3f(+D, -D, +D);
		glTexCoord2f(1, 0); glVertex3f(-D, -D, +D);
		glTexCoord2f(1, 1); glVertex3f(-D, +D, +D);
		glTexCoord2f(0, 1); glVertex3f(+D, +D, +D);
		glEnd();
	}

	if (facePresent[RIGHT]){
		//glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, faceID[RIGHT]);
		//glBindTexture(GL_TEXTURE_CUBE_MAP_POSITIVE_X, skyID);
		glBegin(GL_QUADS);
		glTexCoord2f(0, 0); glVertex3f(-D, -D, -D);
		glTexCoord2f(1, 0); glVertex3f(+D, -D, -D);
		glTexCoord2f(1, 1); glVertex3f(+D, +D, -D);
		glTexCoord2f(0, 1); glVertex3f(-D, +D, -D);
		glEnd();
	}


	/* Top and Bottom */
	if (facePresent[TOP]){
		//glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_2D, faceID[TOP]);
		glBegin(GL_QUADS);
		//glBindTexture(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, skyID);
		glTexCoord2f(0, 0); glVertex3f(-D, +D, -D);
		glTexCoord2f(1, 0); glVertex3f(+D, +D, -D);
		glTexCoord2f(1, 1); glVertex3f(+D, +D, +D);
		glTexCoord2f(0, 1); glVertex3f(-D, +D, +D);
		glEnd();
	}

	if (facePresent[BOTTOM]){
		//glActiveTexture(GL_TEXTURE5);
		glBindTexture(GL_TEXTURE_2D, faceID[BOTTOM]);
		glBegin(GL_QUADS);
		glTexCoord2f(1, 1); glVertex3f(+D, -D, -D);
		glTexCoord2f(0, 1); glVertex3f(-D, -D, -D);
		glTexCoord2f(0, 0); glVertex3f(-D, -D, +D);
		glTexCoord2f(1, 0); glVertex3f(+D, -D, +D);
		glEnd();

	}

	glDisable(GL_TEXTURE_2D);
	//glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	//shader->unbind();
}

void Skybox::render2(){
	glDisable(GL_LIGHTING);
	//glDisable(GL_DEPTH_TEST);	// skybox should be drawn behind anything else
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_TEXTURE_2D);
	//shader->bind();
	glDepthMask(GL_FALSE);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skyID);
	//glBindVertexArray(vao);
	//glDrawArrays(GL_TRIANGLES, 0, 36);
	glBegin(GL_QUADS);
	//glBindTexture(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, skyID);
	glVertex3f(+D, -D, -D);
	glVertex3f(+D, -D, +D);
	glVertex3f(+D, +D, +D);
	glVertex3f(+D, +D, -D);

	glVertex3f(-D, -D, +D);
	glVertex3f(-D, -D, -D);
	glVertex3f(-D, +D, -D);
	glVertex3f(-D, +D, +D);

	glVertex3f(+D, -D, +D);
	glVertex3f(-D, -D, +D);
	glVertex3f(-D, +D, +D);
	glVertex3f(+D, +D, +D);

	glVertex3f(-D, -D, -D);
	glVertex3f(+D, -D, -D);
	glVertex3f(+D, +D, -D);
	glVertex3f(-D, +D, -D);


	glVertex3f(-D, +D, -D);
	glVertex3f(+D, +D, -D);
	glVertex3f(+D, +D, +D);
	glVertex3f(-D, +D, +D);

	glVertex3f(+D, -D, -D);
	glVertex3f(-D, -D, -D);
	glVertex3f(-D, -D, +D);
	glVertex3f(+D, -D, +D);
	glEnd();
	//shader->unbind();
	glEnable(GL_LIGHTING);
	
}

void Skybox::render3(){
	GLint texLoc;
	//shader->bind();
	//texLoc = glGetUniformLocation(shader->pid, "Texture0");
	glUniform1i(texLoc, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, faceID[FRONT]);
	glBindTexture(GL_TEXTURE_2D, faceID[FRONT]);
	
	glBegin(GL_QUADS);
	//glBindTexture(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, skyID);
	glTexCoord2f(0, 0); glVertex3f(+D, -D, -D);
	glTexCoord2f(1, 0); glVertex3f(+D, -D, +D);
	glTexCoord2f(1, 1); glVertex3f(+D, +D, +D);
	glTexCoord2f(0, 1); glVertex3f(+D, +D, -D);
	glEnd();
	//shader->unbind();

}

void Skybox::render4(){
	
	float D = 1.0f;
	/*
	shader[RIGHT]->bind();
	glBegin(GL_QUADS);  // right side
	glVertex3f(+D, -D, -D);
	glVertex3f(+D, -D, +D);
	glVertex3f(+D, +D, +D);
	glVertex3f(+D, +D, -D);
	glEnd();
	shader[RIGHT]->unbind();
	*/
	/*
	shader[LEFT]->bind();
	glBegin(GL_QUADS);  // left side
	glVertex3f(-D, -D, +D);
	glVertex3f(-D, -D, -D);
	glVertex3f(-D, +D, -D);
	glVertex3f(-D, +D, +D);
	glEnd();
	shader[LEFT]->unbind();
	*/
	
	
	///*
	glEnable(GL_TEXTURE_2D);
	//glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, faceID[FRONT]);
	shader[FRONT]->bind();
	glBegin(GL_QUADS);  // front
	glVertex3f(+D, -D, +D);
	glVertex3f(-D, -D, +D);
	glVertex3f(-D, +D, +D);
	glVertex3f(+D, +D, +D);
	glEnd();
	shader[FRONT]->unbind();
	//*/
	///*
	

	//glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, faceID[BACK]);
	shader[BACK]->bind();
	glBegin(GL_QUADS);  // back
	glVertex3f(-D, -D, -D);
	glVertex3f(+D, -D, -D);
	glVertex3f(+D, +D, -D);
	glVertex3f(-D, +D, -D);
	glEnd();
	shader[BACK]->unbind();
	/*
	shader[TOP]->bind();
	glBegin(GL_QUADS);  // top
	glVertex3f(-D, +D, -D);
	glVertex3f(+D, +D, -D);
	glVertex3f(+D, +D, +D);
	glVertex3f(-D, +D, +D);
	glEnd();
	shader[TOP]->unbind();
	*/

}

void Skybox::render5(){
	//glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	/*
	glBindTexture(GL_TEXTURE_CUBE_MAP, skyID);
	skyShader->bind();
	glBindBuffer(GL_ARRAY_BUFFER, SkyBoxVBO);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 12, (void*)0);
	glDrawArrays(GL_QUADS, 0, 24);
	glDisableClientState(GL_VERTEX_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glUseProgram(0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	skyShader->unbind();
	*/
	//glDisable(GL_CULL_FACE);
	//glDisable(GL_DEPTH_TEST);
	//float D = 1.0;
	skyShader->bind();
	glEnable(GL_TEXTURE_CUBE_MAP);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skyID);
	glBegin(GL_QUADS);
	glVertex3f(+D, -D, -D);
	glVertex3f(+D, -D, +D);
	glVertex3f(+D, +D, +D);
	glVertex3f(+D, +D, -D);

	glVertex3f(-D, -D, +D);
	glVertex3f(-D, -D, -D);
	glVertex3f(-D, +D, -D);
	glVertex3f(-D, +D, +D);

	glVertex3f(+D, -D, +D);
	glVertex3f(-D, -D, +D);
	glVertex3f(-D, +D, +D);
	glVertex3f(+D, +D, +D);

	glVertex3f(-D, -D, -D);
	glVertex3f(+D, -D, -D);
	glVertex3f(+D, +D, -D);
	glVertex3f(-D, +D, -D);


	glVertex3f(-D, +D, -D);
	glVertex3f(+D, +D, -D);
	glVertex3f(+D, +D, +D);
	glVertex3f(-D, +D, +D);
	/*
	glVertex3f(+D, -D, -D);
	glVertex3f(-D, -D, -D);
	glVertex3f(-D, -D, +D);
	glVertex3f(+D, -D, +D);
	*/
	glEnd();
	glDisable(GL_TEXTURE_CUBE_MAP);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	skyShader->unbind();
}

void Skybox::render(){
	render5();
}

