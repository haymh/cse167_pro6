uniform sampler2D TopMap;

void main(){

	gl_FragColor = texture2D(TopMap, gl_TexCoord[0].st);

}