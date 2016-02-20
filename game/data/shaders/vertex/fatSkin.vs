
#include "skin.inc"

void main()
{
	vec4 pos = CC_MVPMatrix * skin(vec4(a_position, 1.0), u_matrixPalette);
    vec4 normal = CC_MVPMatrix * vec4(skin(vec4(a_normal, 0.0), u_matrixPalette).xyz, 0.0);
    normal = normalize(normal);
    
	float shift = (0.003 * (pos.z + 1));
	pos += normal * shift;
	
    v_screenPos = pos.xy;
    v_prevScreenPos = pos.xy;
    gl_Position = pos;
	
	v_texCoord = vec2(a_texCoord.x, 1 - a_texCoord.y);
    v_normal = a_normal;
}
