#ifdef GL_ES
precision lowp float;
#else
#define lowp
#define mediump
#define highp

#endif
varying vec4 v_fragmentColor;
varying vec2 v_texCoord;
//uniform sampler2D CC_Texture0;
uniform mediump vec4 uColor;
void main()
{
	gl_FragColor = texture2D(CC_Texture0,v_texCoord);
}