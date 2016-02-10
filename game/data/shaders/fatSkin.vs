
attribute vec3 a_position;
attribute vec4 a_blendWeight;
attribute vec4 a_blendIndex;
attribute vec3 a_normal;
attribute vec2 a_texCoord;

const int SKINNING_JOINT_COUNT = 60;
uniform vec4 u_matrixPalette[SKINNING_JOINT_COUNT * 3];
uniform float fatness;

varying vec2 v_texCoord;
varying vec4 v_pos;

vec4 Skinned(vec4 vec)
{
    float blendWeight = a_blendWeight[0];

    int matrixIndex = int (a_blendIndex[0]) * 3;
    vec4 matrixPalette1 = u_matrixPalette[matrixIndex] * blendWeight;
    vec4 matrixPalette2 = u_matrixPalette[matrixIndex + 1] * blendWeight;
    vec4 matrixPalette3 = u_matrixPalette[matrixIndex + 2] * blendWeight;
    
    blendWeight = a_blendWeight[1];
    if (blendWeight > 0.0)
    {
        matrixIndex = int(a_blendIndex[1]) * 3;
        matrixPalette1 += u_matrixPalette[matrixIndex] * blendWeight;
        matrixPalette2 += u_matrixPalette[matrixIndex + 1] * blendWeight;
        matrixPalette3 += u_matrixPalette[matrixIndex + 2] * blendWeight;
    }
    
    blendWeight = a_blendWeight[2];
    if (blendWeight > 0.0)
    {
        matrixIndex = int(a_blendIndex[2]) * 3;
        matrixPalette1 += u_matrixPalette[matrixIndex] * blendWeight;
        matrixPalette2 += u_matrixPalette[matrixIndex + 1] * blendWeight;
        matrixPalette3 += u_matrixPalette[matrixIndex + 2] * blendWeight;
    }

    blendWeight = a_blendWeight[3];
    if (blendWeight > 0.0)
    {
        matrixIndex = int(a_blendIndex[3]) * 3;
        matrixPalette1 += u_matrixPalette[matrixIndex] * blendWeight;
        matrixPalette2 += u_matrixPalette[matrixIndex + 1] * blendWeight;
        matrixPalette3 += u_matrixPalette[matrixIndex + 2] * blendWeight;
    }

    vec4 _skinnedPosition;
    vec4 position = vec;
    _skinnedPosition.x = dot(position, matrixPalette1);
    _skinnedPosition.y = dot(position, matrixPalette2);
    _skinnedPosition.z = dot(position, matrixPalette3);
    _skinnedPosition.w = position.w;
    
    return _skinnedPosition;
}

void main()
{
	vec4 pos = CC_MVPMatrix * Skinned(vec4(a_position, 1.0));
    vec4 normal = CC_MVPMatrix * vec4(Skinned(vec4(a_normal, 0.0)).xyz, 0.0);
    normal = normalize(normal);
    
	float shift = (0.005 * (pos.z + 1));
	//float shift = 0.1;
	pos += normal * shift;
		
    gl_Position = pos;
	
	v_texCoord = vec2(a_texCoord.x, 1 - a_texCoord.y);
	v_pos = gl_Position;
}
