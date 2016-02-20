
attribute vec3 a_position;
attribute vec3 a_normal;
attribute vec2 a_texCoord;
attribute vec4 a_blendWeight;
attribute vec4 a_blendIndex;

varying vec2 v_screenPos;
varying vec2 v_prevScreenPos;
varying vec2 v_texCoord;
varying vec3 v_normal;

const int MAXCOUNT = 20;
uniform vec4 u_matrixPalette[MAXCOUNT * 3];
uniform vec4 u_prevMatrixPalette[MAXCOUNT * 3];
uniform mat4 prevMVP;

vec4 skin(vec4 vec, vec4 palette[MAXCOUNT * 3])
{
    vec4 m[3] = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    
    for (int i = 0; i < 4; i++)
    {
        float weight = a_blendWeight[i];
        if (weight > 0.0)
        {
            int index = int(a_blendIndex[i]) * 3;
            m[0] += palette[index + 0] * weight;
            m[1] += palette[index + 1] * weight;
            m[2] += palette[index + 2] * weight;
        }
    }

    vec4 skinnedPosition;
    skinnedPosition.x = dot(vec, m[0]);
    skinnedPosition.y = dot(vec, m[1]);
    skinnedPosition.z = dot(vec, m[2]);
    skinnedPosition.w = vec.w;
    return skinnedPosition;
}
