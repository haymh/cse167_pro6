#version 140
varying vec2 texCoord;

void main(){	
     texCoord = gl_TexCoord[0].xy;
    gl_Position    = ftransform();
}