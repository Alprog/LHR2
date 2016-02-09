
attribute vec4 a_position;
attribute vec2 a_texCoord1;
attribute vec2 a_texCoord2;

varying vec2 v_texCoord1;
varying vec2 v_texCoord2;
		 
void main()    
{                            
    gl_Position = CC_MVPMatrix * a_position;
    v_texCoord1 = a_texCoord1;
    v_texCoord2 = a_texCoord2;
}