
#include "skin.inc"

varying vec3 v_position;

void main()
{
    vec4 skinPos = skin(vec4(a_position, 1.0), u_matrixPalette);
    gl_Position = CC_MVPMatrix * skinPos;
    	
    vec4 pos = CC_MVMatrix * vec4(a_position, 1.0);
    v_position = pos.xyz / pos.w;
}
