varying vec3 normal;
varying vec2 texCoord;
varying vec3 position;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;
uniform mat4 model_matrix;
void main(void)
{

	// 1. Albedo
	gl_FrontColor = gl_Color;
	texCoord = gl_MultiTexCoord0.xy;
	
	mat4 modelview_matrix = view_matrix*model_matrix;
	// 2. Normals
	normal = vec3(gl_ModelViewMatrix * vec4(gl_Normal,0.0));

	// 3. Depth
	vec4 viewPos = view_matrix * gl_Vertex; // this will transform the vertex into eyespace
    
	// minus because in OpenGL we are looking in the negative z-direction
	// Scaled
	float far = 50.0;
	float near = 1.0;
	float depth = (-viewPos.z-near)/(far-near); // will map near..far to 0..1

	// Position
	gl_Position = projection_matrix*modelview_matrix*gl_Vertex;

	position = modelview_matrix*gl_Vertex;

}