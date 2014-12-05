//uniform samplerCube CubeMap;

uniform sampler2D FrontMap;

void main(){

	gl_FragColor = texture2D(FrontMap, gl_TexCoord[0].st);

}