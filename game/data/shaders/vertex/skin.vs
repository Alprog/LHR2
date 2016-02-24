
#include "skin.inc"

void main()
{
    vec4 pos = CC_MVPMatrix * skin(vec4(a_position, 1.0), u_matrixPalette);
	vec4 prevPos = prevMVP * skin(vec4(a_position, 1.0), u_prevMatrixPalette);
    v_screenPos = pos.xy / pos.w;
    v_prevScreenPos = prevPos.xy / prevPos.w;
    gl_Position = pos;
    
    v_texCoord = vec2(a_texCoord.x, 1 - a_texCoord.y);
	
    v_normal = (CC_MMatrix * skin(vec4(a_normal, 0), u_matrixPalette)).xyz;
}
