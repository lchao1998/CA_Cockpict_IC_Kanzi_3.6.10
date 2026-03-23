precision mediump float;

uniform sampler2D Texture;
uniform float BlendIntensity;
uniform lowp float BlendOffset;

varying vec2 vTexCoord;

void main()
{

    float intensity =1.0 -  smoothstep(0.0,BlendOffset,1.0-vTexCoord.y);

    vec4 color = texture2D(Texture, vec2(vTexCoord.x, 1.0-vTexCoord.y));

    gl_FragColor.rgba = color.rgba * BlendIntensity*intensity;
}