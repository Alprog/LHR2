
attribute vec4 a_position;
attribute vec2 a_texCoord;
attribute vec2 a_texCoord1;
attribute vec3 a_normal;
attribute vec3 a_tangent;
attribute vec4 a_color;

varying vec2 v_texCoord;
varying vec2 v_texCoord1;
varying vec3 v_normal;
varying vec3 v_tangent;
varying vec3 v_eyeDir;
varying vec4 v_color;
varying vec2 v_screenPos;
varying vec2 v_prevScreenPos;

uniform mat4 prevMVP;

void main()
{    
    vec4 pos = CC_MVPMatrix * vec4(a_position.xyz, 0.000);
    vec4 prevPos = prevMVP * vec4(a_position.xyz, 0.000);
    v_screenPos = pos.xy / pos.w;
    v_prevScreenPos = prevPos.xy / prevPos.w;
    
    pos.z = 0.99 * pos.w;
    
    gl_Position = pos;
    
    
    pos = CC_MMatrix * a_position;
    v_eyeDir = normalize(CC_EyePosition - pos.xyz / pos.w);
    
    v_texCoord = a_texCoord;
    v_texCoord1 = a_texCoord1;
	v_color = a_color;
    v_normal = (CC_MMatrix * vec4(a_normal, 0)).xyz;
    v_tangent = (CC_MMatrix * vec4(a_tangent, 0)).xyz;
}