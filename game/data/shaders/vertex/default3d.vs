
attribute vec4 a_position;
attribute vec2 a_texCoord;
attribute vec3 a_normal;
attribute vec4 a_color;

varying vec2 v_texCoord;
varying vec3 v_normal;
varying vec4 v_color;
varying vec2 v_screenPos;
varying vec2 v_prevScreenPos;

uniform mat4 prevMVP;

void main()
{                            
    vec4 pos = CC_MVPMatrix * a_position;
    vec4 prevPos = prevMVP * a_position;
    v_screenPos = pos.xy / pos.w;
    v_prevScreenPos = prevPos.xy / prevPos.w;
    gl_Position = pos;
    
    v_texCoord = vec2(a_texCoord.x, 1 - a_texCoord.y);
	v_color = a_color;
    v_normal = (CC_MVMatrix * vec4(a_normal, 0)).xyz;
}