uniform sampler2D LeftMap;

void main(){

	gl_FragColor = texture2D(LeftMap, gl_TexCoord[0].st);

}