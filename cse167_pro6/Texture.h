#ifndef TEXTURE_H_
#define TEXTURE_H_

#include "parser.h"

class Texture{
public :
	static GLuint generateTexture(char * filename);
	static GLuint loadTexBMP(char* file);
	static void fatal(const char* format, ...);
	static void reverse(void* x, const int n);
	static void loadSideBMP(GLuint texture, GLenum side_target, const char* file_name);
private :
	static int id;
};

#endif