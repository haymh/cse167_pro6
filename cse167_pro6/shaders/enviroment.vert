
void main()
{
//gl_NormalMatrix * 
// gl_ModelViewMatrix *
    vec3 Normal = gl_Normal;
    vec4 Position =  gl_Vertex;
	vec4 cam = vec4(0,10,0,1);
	//cam = gl_ModelViewMatrix * cam;
    vec3 Reflection = reflect(Position.xyz - cam.xyz, normalize(Normal));
    gl_TexCoord[0].stp = vec3(Reflection.x, Reflection.yz);
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}