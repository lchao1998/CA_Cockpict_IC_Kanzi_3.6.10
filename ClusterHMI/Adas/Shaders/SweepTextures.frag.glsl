precision lowp float; 

varying mediump vec2 vTexCoord;
uniform sampler2D Texture;
uniform sampler2D Texture2;
uniform float BlendIntensity;
uniform float offset;
uniform float smoothing;

void main()
{    
    vec2 uv = vTexCoord;    
    vec4 texture1 = texture2D(Texture, vTexCoord);
    vec4 texture2 = texture2D(Texture2, vTexCoord);   

    float  mask = smoothstep(uv.x, uv.x+smoothing, (offset+1.0));    
    gl_FragColor.rgb = mix(texture1, texture2, mask).rgb * BlendIntensity;

    gl_FragColor.a = BlendIntensity;
}