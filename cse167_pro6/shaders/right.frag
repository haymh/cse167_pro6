uniform sampler2D RightMap;

void main(){

	gl_FragColor = texture2D(RightMap, gl_TexCoord[0].st);

}