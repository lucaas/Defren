uniform sampler2D tex_albedo;
uniform sampler2D tex_normal;
uniform sampler2D tex_position;
uniform sampler2D tex_shininess;

uniform vec3 light_pos;
uniform vec3 light_color;
uniform float light_radius;
uniform float light_intensity;

varying vec2 texCoord;


void main(void) {

	// Sample textures
	vec3 normal = texture2D(tex_normal, texCoord).xyz;
	vec3 albedo = texture2D(tex_albedo, texCoord).xyz;
	vec3 position = texture2D(tex_position, texCoord).xyz;
	vec3 shininess = texture2D(tex_shininess, texCoord).xyz;

	// Unpack data
	//position = 2.0*position - 1.0;
	normal = 2.0*normal - 1.0;

	// LIGHTING
	vec3 vec_light = light_pos - position;
	float dist = length(vec_light);

	float intensity = light_intensity; //light_intensity / (1.0+light_radius*dist);

	
	if (intensity > 0.0) {
		vec3 N = normalize(normal);
		vec3 L = normalize(vec_light-position);   
		vec3 V = normalize(-position); // we are in Eye Coordinates, so EyePos is (0,0,0)
		vec3 R = normalize(reflect(L,N));  // PHONG
		//vec3 H = normalize(L+V);
	   //calculate Ambient Term:  
	   vec4 Iamb = vec4(0); //vec4(0.2*albedo,1.0);

	   //calculate Diffuse Term:  
	   vec4 Idiff = vec4(albedo * max(dot(N,L), 0.0), 1.0);
	   Idiff = clamp(Idiff, 0.0, 1.0);     
   
	   // calculate Specular Term:
	   //vec4 Ispec = vec4(0);
	   //vec4 Ispec = vec4(shininess * pow(max(dot(R,V),0.0),0.3*10.0), 1.0);

	   float materialShininess = 100.0;
	   float specular = pow( max(dot(R, V), 0.0), materialShininess );
	   vec4 Ispec = specular * vec4(shininess, 1);
    
	   // write Total Color:  
	   vec4 objectColor = Iamb + Idiff + Ispec;

		gl_FragColor = intensity * vec4(light_color, 1.0) * objectColor;
	}
	else {
		gl_FragColor = vec4(0.0);
	}
}
