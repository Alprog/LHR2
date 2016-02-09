
attribute vec4 a_position;
attribute vec2 a_texCoord;
attribute vec4 a_color;

varying vec2 v_texCoord;
varying vec2 v_blurTexCoords[10];
varying float alpha;
                               
void main()
{
    gl_Position = CC_PMatrix * a_position;
    v_texCoord = a_texCoord;
	alpha = a_color.a;
    v_blurTexCoords[0] = v_texCoord + vec2(-0.020, 0.0);
    v_blurTexCoords[1] = v_texCoord + vec2(-0.016, 0.0);
    v_blurTexCoords[2] = v_texCoord + vec2(-0.012, 0.0);
    v_blurTexCoords[3] = v_texCoord + vec2(-0.008, 0.0);
    v_blurTexCoords[4] = v_texCoord + vec2(-0.004, 0.0);
    v_blurTexCoords[5] = v_texCoord + vec2(0.004, 0.0);
    v_blurTexCoords[6] = v_texCoord + vec2(0.008, 0.0);
    v_blurTexCoords[7] = v_texCoord + vec2(0.012, 0.0);
    v_blurTexCoords[8] = v_texCoord + vec2(0.016, 0.0);
    v_blurTexCoords[9] = v_texCoord + vec2(0.020, 0.0);
}
