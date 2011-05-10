
varying vec2 texCoord;
varying vec3 viewDir;

void main(void)
{
	texCoord = gl_MultiTexCoord0.xy;
	gl_Position = ftransform();

	viewDir = vec3(gl_ModelViewMatrix * gl_Vertex);       

}