varying vec3 normal;
varying vec2 texCoord;
varying float depth;

void main(void)
{

	// 1. Albedo
	texCoord = gl_MultiTexCoord0.xy;

	// 2. Normals
	normal = normalize(gl_NormalMatrix * gl_Normal);

	// 3. Depth
	vec4 viewPos = gl_ModelViewMatrix * gl_Vertex; // this will transform the vertex into eyespace
    
	// minus because in OpenGL we are looking in the negative z-direction
	// Scaled
	float far = 1.5;
	float near = 0.0;
	depth = (-viewPos.z-near)/(far-near); // will map near..far to 0..1

	// Position
	gl_Position = ftransform();
}