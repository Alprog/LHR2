
attribute vec4 a_position;
attribute vec3 a_normal;
attribute vec2 a_texCoord;

varying vec3 v_position;
varying float v_depth;
varying vec2 v_texCoord;
varying vec3 v_normal;

void main()
{
    gl_Position = CC_MVPMatrix * a_position;
    
    vec4 pos = CC_MVMatrix * a_position;
    v_position = pos.xyz / pos.w;
    
    
    v_depth = (gl_Position.z / pos.w) / 2 + 0.5;
    
    //normal = (CC_MVPMatrix * vec4(a_normal, 0)).rgb;
    //v_texCoord = a_texCoord;
}