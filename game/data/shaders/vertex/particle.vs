
attribute vec4 a_position;
attribute vec2 a_texCoord;
attribute vec4 a_color;
attribute vec4 a_texCoord2; // x: size

varying vec2 v_texCoord;
varying vec4 v_color;

void main()    
{                            
	vec4 pos = a_position;
	pos.w = 1;
	
	vec2 shift = (a_texCoord - 0.5) * a_texCoord2.x;
	
	pos = CC_MVPMatrix * pos;		
	
	pos.x += shift.x * CC_PMatrix[0][0] * length(CC_MVMatrix[0].xyz);
	pos.y += shift.y * CC_PMatrix[1][1] * length(CC_MVMatrix[1].xyz);
		
    gl_Position = pos;
	
    v_texCoord = a_texCoord;
	v_color = a_color;
}