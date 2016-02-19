
attribute vec4 a_position;
attribute vec2 a_texCoord;
attribute vec3 a_normal;
attribute vec4 a_color;

varying vec2 v_texCoord;
varying vec3 v_normal;
varying vec4 v_color;
	
void main()    
{                            
    gl_Position = CC_MVPMatrix * a_position;
    v_texCoord = vec2(a_texCoord.x, 1 - a_texCoord.y);
	v_color = a_color;
    v_normal = a_normal;
}