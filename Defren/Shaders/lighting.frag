uniform sampler2D tex_albedo;
uniform sampler2D tex_normal;
uniform sampler2D tex_depth;
//uniform sampler2D tex_shininess;

varying vec2 texCoord;
varying vec3 viewDir;

void main(void) {
	vec3 normal = texture2D(tex_normal, texCoord).xyz;
	vec3 N = 2.0*normal - 1.0;
	vec3 albedo = texture2D(tex_albedo, texCoord).xyz;
	vec3 depth = texture2D(tex_depth, texCoord).xyz;
	vec3 shininess = texture2D(tex_depth, texCoord).xyz;

	// LIGHTING
	vec3 L = normalize(vec3(1.0,1.0,1.0));   
	vec3 V = normalize(-viewDir); // we are in Eye Coordinates, so EyePos is (0,0,0)  
	vec3 R = normalize(-reflect(L,N));  // PHONG

   //calculate Ambient Term:  
   vec4 Iamb = vec4(0.2*albedo,1.0);

   //calculate Diffuse Term:  
   vec4 Idiff = vec4(albedo * max(dot(N,L), 0.0), 1.0);
   Idiff = clamp(Idiff, 0.0, 1.0);     
   
   // calculate Specular Term:
   vec4 Ispec = vec4(0.2*albedo,1.0);
   //Ispec = Ispec * pow(max(dot(R,V),0.0),0.3*shininess.r);
   //Ispec = clamp(Ispec, 0.0, 1.0);
    
   // write Total Color:  
   vec4 lightColor = Iamb + Idiff + Ispec;

	// vec4 color = vec4(0.33 * (normal + albedo + depth), 1);
	// vec4 color = vec4(normal, 1);
	gl_FragColor = lightColor;

}