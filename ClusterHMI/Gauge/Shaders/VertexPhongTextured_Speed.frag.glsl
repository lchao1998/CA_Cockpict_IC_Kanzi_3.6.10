uniform lowp float BlendIntensity;
uniform lowp vec4 Ambient;

#if KANZI_SHADER_USE_BASECOLOR_TEXTURE
uniform mediump vec2 TextureOffset;
varying mediump vec2 vTexCoord;
uniform sampler2D Texture;
uniform sampler2D TextureBg;
uniform sampler2D TextureFg;
#endif

#if KANZI_SHADER_NUM_SPOT_LIGHTS || KANZI_SHADER_NUM_POINT_LIGHTS || KANZI_SHADER_NUM_DIRECTIONAL_LIGHTS
varying lowp vec3 vAmbDif;
varying lowp vec3 vSpec;
#endif

#if KANZI_SHADER_USE_REFLECTION_CUBE
varying mediump vec3 vViewDirection;
varying lowp vec3 vNormal;
uniform lowp samplerCube TextureCube;
uniform lowp vec4        CubemapColor;
#endif

void main()
{
    precision lowp float;       
    lowp vec3 color = vec3(0.0); 
    
#if KANZI_SHADER_USE_BASECOLOR_TEXTURE
    vec4 colorbg = texture2D(TextureBg, vTexCoord).rgba;
    vec4 colorfg = texture2D(TextureFg, vTexCoord+TextureOffset)*step(0.2, vTexCoord.y);
    lowp vec4 baseColor = colorbg * (1.0-colorfg.a) + colorfg;
    //lowp vec4 baseColor = texture2D(Texture, vTexCoord).rgba;
#else
    lowp vec4 baseColor = vec4(1.0);
#endif
    
    
    
    color += baseColor.rgb;

#if KANZI_SHADER_NUM_SPOT_LIGHTS || KANZI_SHADER_NUM_POINT_LIGHTS || KANZI_SHADER_NUM_DIRECTIONAL_LIGHTS
    color *= vAmbDif;
    color += vSpec;
#endif
    
#if KANZI_SHADER_USE_REFLECTION_CUBE
    vec3 R = reflect(normalize(vViewDirection), normalize(vNormal));
    color += textureCube(TextureCube, R).rgb * CubemapColor.rgb;
#endif

    gl_FragColor = vec4(color, baseColor.a) * BlendIntensity;
}