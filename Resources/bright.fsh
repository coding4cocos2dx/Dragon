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
    vec4 col = texture2D(CC_Texture0,v_texCoord);
    
    float r = col.r*1.4;
    float g = col.g*1.4;
    float b = col.b*1.4;
    
	gl_FragColor = vec4(r,g,b,col.a);
}