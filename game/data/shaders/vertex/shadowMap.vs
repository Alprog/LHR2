
attribute vec4 a_position;

varying float v_depth;

void main()
{    
    vec4 pos = CC_MVPMatrix * a_position;
    gl_Position = pos;
    v_depth = (pos.z / pos.w) / 2 + 0.5;
}