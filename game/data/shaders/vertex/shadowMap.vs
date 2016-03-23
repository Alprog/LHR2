
attribute vec4 a_position;

varying vec3 v_position;
//varying float v_depth;

void main()
{
    gl_Position = CC_MVPMatrix * a_position;
    vec4 pos = CC_MVMatrix * a_position;
    v_position = pos.xyz / pos.w;
    //v_depth = (gl_Position.z / pos.w) / 2 + 0.5;
}