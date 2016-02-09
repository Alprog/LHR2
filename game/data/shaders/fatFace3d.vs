
attribute vec4 a_position;
attribute vec3 a_normal;
attribute vec2 a_texCoord1;
attribute vec2 a_texCoord2;

varying vec2 v_texCoord1;
varying vec2 v_texCoord2;
varying float brightness;
varying float z;

uniform sampler2D mainTexture;
uniform mat4 mtrx;
uniform mat4 MODEL;
uniform float fatness;

void main()    
{
	vec3 light = vec3(1.0, 0.0, 0.0);

	brightness = 0.1 + 0.9 * dot(light, a_normal);

	vec4 position = a_position / a_position.w;
	position.xyz += a_normal * fatness;  

	z = position.z;
	gl_Position = CC_MVPMatrix * mtrx * position;
    v_texCoord1 = a_texCoord1;
	v_texCoord2 = a_texCoord2;
}