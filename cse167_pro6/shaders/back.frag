uniform sampler2D BackMap;

void main(){

	gl_FragColor = texture2D(BackMap, gl_TexCoord[0].st);

}