
attribute vec4 a_position;
attribute vec2 a_texCoord;

varying vec2 v_texCoord;
varying vec2 v_blurTexCoords[10];

float r = 1.0 / 1024;
                               
void main()
{
    gl_Position = CC_VPMatrix * a_position;
    v_texCoord = a_texCoord;
    v_blurTexCoords[0] = v_texCoord + vec2(-5 * r, 0.0);
    v_blurTexCoords[1] = v_texCoord + vec2(-4 * r, 0.0);
    v_blurTexCoords[2] = v_texCoord + vec2(-3 * r, 0.0);
    v_blurTexCoords[3] = v_texCoord + vec2(-2 * r, 0.0);
    v_blurTexCoords[4] = v_texCoord + vec2(-1 * r, 0.0);
    v_blurTexCoords[5] = v_texCoord + vec2(1 * r, 0.0);
    v_blurTexCoords[6] = v_texCoord + vec2(2 * r, 0.0);
    v_blurTexCoords[7] = v_texCoord + vec2(3 * r, 0.0);
    v_blurTexCoords[8] = v_texCoord + vec2(4 * r, 0.0);
    v_blurTexCoords[9] = v_texCoord + vec2(5 * r, 0.0);
}
