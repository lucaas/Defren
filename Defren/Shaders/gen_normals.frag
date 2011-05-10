varying vec3 normal;

void main (void)  
{  
	vec4 color = vec4(normal.xyz, 1) + 0.5f;
	gl_FragColor = clamp(color, 0, 1);
}

  