#version 110
varying vec3 normal;
varying vec2 texCoord;
varying vec3 position;

uniform sampler2D tex;


void main (void)  
{  

	// 1. Albedo (texture diffuse)
	//gl_FrontColor = gl_Color;
	vec4 texColor = gl_Color * texture2D(tex, texCoord);
	
	// 2. Normals	
	vec4 normalColor = vec4(normalize(normal) * 0.5 + 0.5, 1.0);

	// 3. Position
	vec4 positionColor = vec4(position, 1.0);

	// 4. Shininess?
	vec4 shininessColor = vec4(0.5);

	gl_FragData[0] = texColor;
	gl_FragData[1] = clamp(normalColor, 0.0, 1.0);
	gl_FragData[2] = positionColor;
	gl_FragData[3] = shininessColor;
	
}

  