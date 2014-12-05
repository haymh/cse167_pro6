void main(){
	gl_TexCoord[0].st = vec2(0.5 - (gl_Vertex.z / 2), 0.5 + (gl_Vertex.y / 2));
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;   

}