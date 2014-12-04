#include "glee.h"
#include "Skybox.h"
#include "Texture.h"


Skybox::Skybox(double radius){
	D = radius;
	for (int i = 0; i < 6; i++){
		facePresent[i] = false;
	}
	bs.center = Vector3d(0, 0, 0);
	bs.radius = sqrt(D * D * 2);
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
}

void Skybox::loadFace(face f, char* filename){
	GLuint id = Texture::loadTexBMP(filename);
	facePresent[f] = true;
	faceID[f] = id;
}

void Skybox::loadSkybox(const char* front,
	const char* back,
	const char* top,
	const char* bottom,
	const char* left,
	const char* right){
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
	shader = new Shader("shaders/skybox.vert", "shaders/skybox.frag");
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
	shader->bind();
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
	shader->unbind();
	glEnable(GL_LIGHTING);
	
}

void Skybox::render(){
	render2();
}

