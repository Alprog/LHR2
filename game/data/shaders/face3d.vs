
attribute vec4 a_position;
attribute vec3 a_normal;
attribute vec2 a_texCoord1;
attribute vec2 a_texCoord2;
attribute vec4 a_color;

varying vec2 v_texCoord1;
varying vec2 v_texCoord2;
varying vec4 v_color;

uniform mat4 mtrx;

void main()    
{   
	gl_Position = CC_MVPMatrix * mtrx * a_position;
    v_texCoord1 = a_texCoord1;
	v_texCoord2 = a_texCoord2;
	v_color = a_color;
	
	//vec3 light = vec3(1.0, 0.0, 0.0);
	//v_brightness = 0.1 + 0.9 * dot(light, a_normal);
}