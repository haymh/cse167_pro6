#version 140
uniform sampler2D Texture0;
varying vec2 texCoord;

void main(){
	//gl_FragColor = textureCube(cube, gl_TexCoord[0].stp);
	vec2 a = vec2(0.5,0.5);
	gl_FragColor = texture2D(Texture0, a);
}