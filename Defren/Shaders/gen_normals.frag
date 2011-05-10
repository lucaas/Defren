#version 110
varying vec3 normal;
varying vec2 texCoord;
varying float depth;

uniform sampler2D texture;


void main (void)  
{  
	normalize(normal);
	
	// 1. Albedo (texture diffuse)
	vec4 texColor = texture2D(texture, texCoord);
	
	// 2. Normals	
	vec4 normalColor = (vec4(normal.xyz, 1) + 1.0) / 2.0;

	// 3. Depth
	vec4 depthColor = vec4(depth);

	// 4. Shininess?
	vec4 shininessColor = vec4(100);

	gl_FragData[0] = texColor;
	gl_FragData[1] = clamp(normalColor, 0.0, 1.0);
	gl_FragData[2] = clamp(depthColor, 0.0, 1.0);
	gl_FragData[3] = shininessColor;
	
}

  