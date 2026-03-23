#version 300 es
#define PI 3.1415926535

precision highp float;

uniform vec4  PBR_GlobalAmbient;
uniform vec4  PBR_Ambient;
uniform vec4  PBR_LightColor;
uniform float KanziPBR_Roughness;
uniform float PBR_Metalness;
uniform vec4  PBR_Emissive;
uniform float PBR_EmissiveIntensity;
uniform float BlendIntensity;
uniform mediump float PBR_HardShading;

in  vec3 vNormalRotated;
in  vec3 vNormal;
in  vec3 vViewDirectionRotated;
in  vec3 vViewDirection;
in  vec4 vColor;

out  vec4  outColor;

uniform  float Exposure;
uniform  float A;
uniform  float B;
uniform  float C;
uniform  float D;
uniform  float E;
uniform  float F;
uniform  float W;
uniform  float ReflectionStrength;
uniform  float ReflectionStrengthLocal;
uniform  float AmbientStrength;
uniform  float FresnelStrength;
uniform  float FresnelStrengthLocal;

#if TEXTURE_MODEL_ALBEDO || TEXTURE_MODEL_ROUGHNESS || TEXTURE_MODEL_METALNESS || TEXTURE_MODEL_NORMALMAP || TEXTURE_MODEL_OCCLUSION || TEXTURE_MODEL_EMISSIVE
in  vec2   vTexCoord;
#endif

#if (TEXTURE_TILABLE_EMISSIVE >= 2)
in  vec2 vTexCoord1;
#endif

#if TEXTURE_TILABLE_ALBEDO || TEXTURE_TILABLE_ROUGHNESS || TEXTURE_TILABLE_METALNESS || TEXTURE_TILABLE_NORMALMAP || TEXTURE_TILABLE_OCCLUSION || TEXTURE_TILABLE_EMISSIVE
in  vec2   vTilableCoord;
#endif

#if TEXTURE_MODEL_NORMALMAP || TEXTURE_TILABLE_NORMALMAP
in  vec3          vTangent;
in  vec3          vBinormal;
#endif

#if TEXTURE_MODEL_NORMALMAP
uniform sampler2D         KanziPBR_Tex_NormalMap;
uniform float           KanziPBR_NormalMapStrength;
#endif

#if TEXTURE_TILABLE_NORMALMAP
uniform sampler2D        PBR_Tex_Noise_NormalMap;
uniform float             PBR_Noise_NormalMapStrength;
#endif

#if TEXTURE_MODEL_ALBEDO && TEXTURE_TILABLE_ALBEDO
uniform sampler2D        KanziPBR_Tex_Albedo;
uniform vec4             PBR_Albedo;
uniform sampler2D        KanziPBR_Tex_Tilable_Albedo;
uniform vec4           KanziPBR_Tilable_Albedo;

#elif TEXTURE_MODEL_ALBEDO
uniform sampler2D        KanziPBR_Tex_Albedo;
uniform vec4            PBR_Albedo;

#elif TEXTURE_TILABLE_ALBEDO
uniform sampler2D        KanziPBR_Tex_Tilable_Albedo;
uniform vec4           KanziPBR_Tilable_Albedo;
uniform vec4           PBR_Albedo;

#else
uniform vec4           PBR_Albedo;
#endif

#if TEXTURE_MODEL_ROUGHNESS
uniform sampler2D        KanziPBR_Tex_Roughness;
uniform float           KanziPBR_RoughnessOffset;
#endif

#if TEXTURE_TILABLE_ROUGHNESS
uniform float            PBR_Noise_Roughness;
uniform sampler2D        PBR_Tex_Noise_Roughness;
uniform float            PBR_Noise_RoughnessOffset;
#endif

#if TEXTURE_MODEL_METALNESS
uniform sampler2D        KanziPBR_Tex_Metalness;
uniform float            PBR_MetalnessOffset;
#endif

#if TEXTURE_TILABLE_METALNESS
uniform float            KanziPBR_Tilable_Metalness;
uniform sampler2D         KanziPBR_Tex_Tilable_Metalness;
uniform float            KanziPBR_Tilable_MetalnessOffset;
#endif

#if TEXTURE_MODEL_OCCLUSION
uniform sampler2D        PBR_Tex_Noise_AmbientOcclusion;
uniform float           PBR_AmbientOcclusionStrength;
#endif

#if TEXTURE_TILABLE_OCCLUSION
uniform sampler2D        PBR_Tex_Noise_AmbientOcclusion;
uniform float            PBR_AmbientOcclusionStrength;
#endif

#if TEXTURE_MODEL_EMISSIVE
uniform sampler2D        KanziPBR_Tex_Emissive;
#endif

#if TEXTURE_TILABLE_EMISSIVE
uniform  vec4      KanziPBR_Tilable_Emissive;
uniform sampler2D        KanziPBR_Tex_Tilable_Emissive;
#if (TEXTURE_TILABLE_EMISSIVE == 3)
uniform  vec4      KanziPBR_Tilable_EmissiveMultiplier;
#endif
#endif


#if CLEARCOAT
uniform  float     PBR_ClearCoat_Strength;
uniform  float     PBR_ClearCoat_Roughness;
uniform  float     PBR_ClearCoat_SpecularRoughness;
uniform  float     PBR_ClearCoat_Metalness;
#endif

#if LIGHT_IMAGE_BASED 
uniform samplerCube    PBR_Tex_Cube_Diffuse;
uniform samplerCube    PBR_Tex_Cube_Reflection;
#endif

#if LIGHTS_DIRECTIONAL
uniform vec4              DirectionalLightColor[LIGHTS_DIRECTIONAL];
in  vec3        vDirectionalLightDirection[LIGHTS_DIRECTIONAL];
#endif

#if LIGHTS_POINT
uniform vec4            PointLightColor[LIGHTS_POINT];
uniform  vec3   PointLightAttenuation[LIGHTS_POINT];
in  vec3        vPointLightDirection[LIGHTS_POINT];
#endif

#if LIGHTS_SPOT
uniform vec4                SpotLightColor[LIGHTS_SPOT];
uniform  vec3     SpotLightDirection[LIGHTS_SPOT];
uniform  vec3     SpotLightConeParameters[LIGHTS_SPOT];
uniform  vec3     SpotLightAttenuation[LIGHTS_SPOT];
in  vec3             vSpotLightDirection[LIGHTS_SPOT];
#endif

vec4 screenSpaceDither()
{
    vec3 dither = vec3(dot( vec2( 171.0, 231.0 ), gl_FragCoord.xy));
    dither.rgb = fract( dither.rgb / vec3( 103.0, 71.0, 97.0 ) ) - vec3( 0.5, 0.5, 0.5 );
    return vec4(( dither.rgb / 255.0 ) * 0.375, 0.0);
}

float curvature(vec3 N)
{
    vec3 fWidth = fwidth(N);
    float clampedDot = max( min( dot( fWidth, fWidth ), 1.0 ), 0.0 );
    return pow( clampedDot, 0.333 );
}

 float Distribution( float NdotH, float roughness)
{
     float a = max(roughness * roughness, 0.001);
     float a2 = a * a;
     float NdotH2 = NdotH * NdotH;
     float f = (NdotH2 * (a2 - 1.0) + 1.0);
    return a2 / (PI * f * f);
}

 float Geometry( float NdotV,  float NdotL, float roughness)
{
    float a = roughness + 1.0;
    float k = (a * a) / 8.0;
     float GGXV = NdotV / (NdotV * (1.0 - k) + k);
     float GGXL = NdotL / (NdotL * (1.0 - k) + k);
    return GGXV * GGXL;
}

vec3 Uncharted2ToneMapping(vec3 color)
{
    color *= Exposure;
    color = ((color * (A * color + C * B) + D * E) / (color * (A * color + B) + D * F)) - E / F;
    float white = ((W * (A * W + C * B) + D * E) / (W * (A * W + B) + D * F)) - E / F;
    color /= white;
    return color;
}

 float ClearCoatGeometry( float LdotH, float roughness)
{
    float a = roughness / 2.0;
    float k = a * a;
    float invK = 1.0 - k;
    return 1.0 / (LdotH * LdotH * invK + k);
}

 vec3 Fresnel( float cosT, vec3 F0)
{
  return F0 + (1.0-F0) * pow( 1.0 - cosT, 5.0);
}

 vec3 Tonemap( vec3 color)
{
     vec3 uc2Tonemapper = Uncharted2ToneMapping(max(color, vec3(0.00001)));
     vec3 outColor = pow(uc2Tonemapper, vec3(0.4545));
    return outColor;
}

void main()
{
     vec3 color = vec3(0.0);
     vec3 V = normalize(vViewDirection);
     vec3 Vrot = normalize(vViewDirectionRotated);
    
#if TEXTURE_MODEL_ALBEDO && TEXTURE_TILABLE_ALBEDO 
    vec4 tilableAlbedo = vec4(vec3(pow(texture(KanziPBR_Tex_Tilable_Albedo, vTilableCoord).rgb, vec3(2.2))) * KanziPBR_Tilable_Albedo.rgb, texture(KanziPBR_Tex_Tilable_Albedo, vTilableCoord).a);
    vec4 modelAlbedo = mix(vec4(PBR_Albedo.rgb, 1.0), vec4(vec3(pow(texture(KanziPBR_Tex_Albedo, vTexCoord).rgb, vec3(2.2))) * PBR_Albedo.rgb, texture(KanziPBR_Tex_Albedo, vTexCoord).a), PBR_Albedo.a);
    vec4 albedo = mix(modelAlbedo, modelAlbedo * (1.0 - vec4(tilableAlbedo.a)) + tilableAlbedo, KanziPBR_Tilable_Albedo.a);
    
#elif TEXTURE_MODEL_ALBEDO
    vec4 albedo = mix(vec4(PBR_Albedo.rgb, 1.0), vec4(vec3(pow(texture(KanziPBR_Tex_Albedo, vTexCoord).rgb, vec3(2.2))) * PBR_Albedo.rgb, texture(KanziPBR_Tex_Albedo, vTexCoord).a), PBR_Albedo.a);
  
#elif TEXTURE_TILABLE_ALBEDO
    vec4 tilableAlbedo = vec4(vec3(pow(texture(KanziPBR_Tex_Tilable_Albedo, vTilableCoord).rgb, vec3(2.2))) * KanziPBR_Tilable_Albedo.rgb, texture(KanziPBR_Tex_Tilable_Albedo, vTilableCoord).a);
    vec4 modelAlbedo = PBR_Albedo;
    vec4 albedo = mix(modelAlbedo, modelAlbedo * (1.0 - vec4(tilableAlbedo.a)) + tilableAlbedo, KanziPBR_Tilable_Albedo.a);
    
#else
    vec4 albedo = PBR_Albedo;

#endif

#if TEXTURE_MODEL_METALNESS && TEXTURE_TILABLE_METALNESS
    float tilableMetalness = texture(KanziPBR_Tex_Tilable_Metalness, vTilableCoord).r * KanziPBR_Tilable_Metalness + KanziPBR_Tilable_MetalnessOffset;
    float metalness = clamp((texture(KanziPBR_Tex_Metalness, vTexCoord).r * PBR_Metalness + PBR_MetalnessOffset) * tilableMetalness, 0.0, 1.0);
    
#elif TEXTURE_MODEL_METALNESS
    float metalness = clamp(texture(KanziPBR_Tex_Metalness, vTexCoord).r * PBR_Metalness + PBR_MetalnessOffset, 0.0, 1.0);
    
#elif TEXTURE_TILABLE_METALNESS
    float metalness = clamp(texture(KanziPBR_Tex_Tilable_Metalness, vTilableCoord).r * KanziPBR_Tilable_Metalness + KanziPBR_Tilable_MetalnessOffset, 0.0, 1.0);

#else
    float metalness = clamp(PBR_Metalness, 0.0, 1.0);

#endif


#if TEXTURE_MODEL_ROUGHNESS && TEXTURE_TILABLE_ROUGHNESS
    float tilableRoughness = texture(PBR_Tex_Noise_Roughness, vTilableCoord).r * PBR_Noise_Roughness + PBR_Noise_RoughnessOffset;
    float roughness = clamp(texture(KanziPBR_Tex_Roughness, vTexCoord).r * KanziPBR_Roughness + KanziPBR_RoughnessOffset + tilableRoughness, 0.0, 1.0);
    
#elif TEXTURE_MODEL_ROUGHNESS
    float roughness = clamp(texture(KanziPBR_Tex_Roughness, vTexCoord).r * KanziPBR_Roughness + KanziPBR_RoughnessOffset, 0.0, 1.0);
    
#elif TEXTURE_TILABLE_ROUGHNESS
    float roughness = clamp(texture(PBR_Tex_Noise_Roughness, vTilableCoord).r * PBR_Noise_Roughness + PBR_Noise_RoughnessOffset, 0.0, 1.0);
    
#else
    float roughness = clamp(KanziPBR_Roughness, 0.0, 1.0);
    
#endif

#if TEXTURE_MODEL_EMISSIVE && TEXTURE_TILABLE_EMISSIVE
    vec4 tilableEmissiveTex = texture(KanziPBR_Tex_Tilable_Emissive, vTilableCoord);
    
    vec4 emissiveTex = vec4(0.0);
    
#if (TEXTURE_TILABLE_EMISSIVE == 2)
    emissiveTex = texture(KanziPBR_Tex_Emissive, vTexCoord1);
#else
    emissiveTex = texture(KanziPBR_Tex_Emissive, vTexCoord);
#endif
    
    vec4 tilableEmissive = mix(vec4(0.0), vec4(tilableEmissiveTex.rgb * KanziPBR_Tilable_Emissive.rgb, tilableEmissiveTex.a), KanziPBR_Tilable_Emissive.a);
    //vec3 emissive = mix(PBR_Emissive.rgb, emissiveTex.rgb * PBR_Emissive.rgb, PBR_Emissive.a);
    //emissive *= 1.0 - tilableEmissive.a;
    vec3 emissive = tilableEmissive.rgb * emissiveTex.rgb;
    
#elif TEXTURE_MODEL_EMISSIVE
    vec3 emissive = texture(KanziPBR_Tex_Emissive, vTexCoord).rgb * PBR_Emissive.rgb;
    
#elif TEXTURE_TILABLE_EMISSIVE
    vec3 emissive = texture(KanziPBR_Tex_Tilable_Emissive, vTilableCoord).rgb * KanziPBR_Tilable_Emissive.rgb;
    
#else
    vec3 emissive = PBR_Emissive.rgb;
    
#endif

#if (TEXTURE_TILABLE_EMISSIVE == 3)
    emissive *= KanziPBR_Tilable_EmissiveMultiplier.rgb;
#endif

#if TEXTURE_MODEL_OCCLUSION && TEXTURE_TILABLE_OCCLUSION
    float tilableAO = mix(1.0, texture(PBR_Tex_Noise_AmbientOcclusion, vTilableCoord).r, PBR_AmbientOcclusionStrength);
    vec2 AO = clamp(mix(1.0, texture(PBR_Tex_Noise_AmbientOcclusion, vTexCoord).r, PBR_AmbientOcclusionStrength) * tilableAO, 0.0, 1.0);
    
#elif TEXTURE_MODEL_OCCLUSION
    float AO = clamp(1.0 - (1.0 - texture(PBR_Tex_Noise_AmbientOcclusion, vTexCoord).r) * PBR_AmbientOcclusionStrength, 0.0, 1.0);

#elif TEXTURE_TILABLE_OCCLUSION
    float AO = clamp(1.0 - (1.0 - texture(PBR_Tex_Noise_AmbientOcclusion, vTilableCoord).r) * PBR_AmbientOcclusionStrength, 0.0, 1.0);
        
#else
    float AO = 1.0;

#endif

    float cavity = smoothstep(0.0, 0.2, AO);
    
    //AO = AO + (1.0-cavity);
    
#if TEXTURE_MODEL_NORMALMAP && TEXTURE_TILABLE_NORMALMAP
     vec3 baseNormal = texture(KanziPBR_Tex_NormalMap, vTexCoord).xyz;
     vec3 baseNormalFactor = mix(vec3(0.0, 0.0, 1.0), baseNormal * 2.0 - 1.0, KanziPBR_NormalMapStrength);
     vec3 tilableNormal = texture(PBR_Tex_Noise_NormalMap, vTilableCoord).xyz;
     vec3 tilableNormalFactor = mix(vec3(0.0, 0.0, 1.0), tilableNormal * 2.0 - 1.0, PBR_Noise_NormalMapStrength);
     vec3 NormalFactor = vec3(baseNormalFactor.xy + tilableNormalFactor.xy, baseNormalFactor.z);
     vec3 N = normalize(vec3(vTangent * NormalFactor.x + 
                  vBinormal * NormalFactor.y +
                  vNormal * NormalFactor.z));

#elif TEXTURE_MODEL_NORMALMAP
     vec3 textureNormal = texture(KanziPBR_Tex_NormalMap, vTexCoord).xyz;
     vec3 NormalFactor = mix(vec3(0.0, 0.0, 1.0), textureNormal * 2.0 - 1.0, KanziPBR_NormalMapStrength);
     vec3 N = normalize(vec3(vTangent * NormalFactor.x + 
                  vBinormal * NormalFactor.y +
                  vNormal * NormalFactor.z));
                  
#elif TEXTURE_TILABLE_NORMALMAP
     vec3 textureNormal = texture(PBR_Tex_Noise_NormalMap, vTilableCoord).xyz;
     vec3 NormalFactor = mix(vec3(0.0, 0.0, 1.0), textureNormal * 2.0 - 1.0, PBR_Noise_NormalMapStrength);
     vec3 N = normalize(vec3(vTangent * NormalFactor.x + 
                  vBinormal * NormalFactor.y +
                  vNormal * NormalFactor.z));                  
#else
     vec3 N = normalize(vNormal);
    
#endif

     float curv = curvature(normalize(vNormal));
    roughness = max(curv, roughness);
           
vec3 NRot = normalize(vNormalRotated);

#if LIGHT_IMAGE_BASED && CLEARCOAT

    //Calculate Base Layer lighting
    vec3 R = reflect(Vrot, NRot);
    vec3 F0 = mix(vec3(0.04), albedo.rgb, metalness);
    float NdotV = clamp(max(0.0, dot(N, -V)), 0.0, 1.0);
    vec3 fresnel = Fresnel(NdotV, F0) * mix(vec3(1.0), albedo.rgb, metalness);
    
    vec3 ambientCube = texture(PBR_Tex_Cube_Diffuse, NRot).rgb * PBR_Ambient.rgb * PBR_GlobalAmbient.rgb;
    vec3 ambientColor = mix(ambientCube, vec3(0.0), metalness) * albedo.rgb * vColor.rgb * AO * AmbientStrength;
    
    vec3 reflectionCube = textureLod(PBR_Tex_Cube_Reflection, R, roughness * float(LIGHT_IMAGE_BASED)).rgb * PBR_GlobalAmbient.rgb * PBR_Ambient.rgb;
    vec3 reflectionColor = reflectionCube * pow(vColor.r, 0.2)  * fresnel * AO * cavity * ReflectionStrength * ReflectionStrengthLocal;
    
    //Calculate Clear Coat
    vec3 ccF0 = mix(vec3(0.04), albedo.rgb, PBR_ClearCoat_Metalness);
    float ccRoughness = mix(0.03, 0.6, PBR_ClearCoat_Roughness);
    vec3 rawNormal = normalize(vNormal);
    vec3 ccR = reflect(Vrot, NRot);
    float ccNdotV = max(0.0, dot(rawNormal, -V));
    vec3 ccFresnel = Fresnel(ccNdotV, ccF0) * PBR_ClearCoat_Strength * mix(vec3(1.0), albedo.rgb, PBR_ClearCoat_Metalness);
    
    vec3 ccReflectionCube = textureLod(PBR_Tex_Cube_Reflection, ccR, ccRoughness * float(LIGHT_IMAGE_BASED)).rgb;
    
    vec3 ccColor = ccReflectionCube * PBR_Ambient.rgb * PBR_GlobalAmbient.rgb * ccFresnel * AO * cavity * FresnelStrength * FresnelStrengthLocal;
    
    color += (ambientColor + reflectionColor * (1.0-ccFresnel)) * (1.0-ccFresnel) + ccColor;

#elif LIGHT_IMAGE_BASED
     vec3 R = reflect(Vrot, NRot);
    vec3 F0 = mix(vec3(0.04), albedo.rgb, metalness);
     float NdotV = clamp(max(0.0, dot(N, -V)), 0.0, 1.0);
     vec3 fresnel = Fresnel(NdotV, F0) * mix(vec3(1.0), albedo.rgb, metalness);
    
    vec3 ambientCube = texture(PBR_Tex_Cube_Diffuse, NRot).rgb * vColor.rgb * PBR_GlobalAmbient.rgb * PBR_Ambient.rgb;
    vec3 ambientColor = mix(ambientCube, vec3(0.0), metalness) * albedo.rgb * AO * AmbientStrength;
    
    vec3 reflectionCube = textureLod(PBR_Tex_Cube_Reflection, R, roughness * float(LIGHT_IMAGE_BASED)).rgb * PBR_GlobalAmbient.rgb  * PBR_Ambient.rgb;
    vec3 reflectionColor = reflectionCube* fresnel * AO * cavity * ReflectionStrength * ReflectionStrengthLocal; 
    
    color += ambientColor + reflectionColor;
 
#else
    color += PBR_Ambient.rgb * albedo.rgb * AO * cavity;

#endif


#if LIGHTS_DIRECTIONAL || LIGHTS_POINT || LIGHTS_SPOT
    int i;
#endif

mediump float mainLight;

#if LIGHTS_DIRECTIONAL && CLEARCOAT
    for (i = 0; i < LIGHTS_DIRECTIONAL; ++i)
    {
        vec3 L = vDirectionalLightDirection[i];
        vec3 H = normalize(-V + L);
        
        float NdotH = clamp(max(0.0, dot(N, H)), 0.0, 1.0);
        float NdotV = clamp(max(0.0, dot(N, -V)), 0.0, 1.0);
        float NdotL = clamp(max(0.0, dot(N, L)), 0.0, 1.0);
        float HdotV = clamp(max(0.0, dot(H, -V)), 0.0, 1.0);
        
        vec3 F0 = mix(vec3(0.04), albedo.rgb, metalness);
        float dist = Distribution(NdotH, roughness);
        float geo = Geometry(NdotV, NdotL, roughness);
        // vec3 fresnel = Fresnel(HdotV, F0);
        vec3 fresnel = Fresnel(NdotV, F0);
        vec3 specularNum = (dist * geo) * fresnel;
        float specularDenom = max(0.004, 4.0 * NdotV * NdotH);
        vec3 specular = specularNum / specularDenom;
        vec3 diffuse =  ((1.0 / PI) *  albedo.rgb) * (1.0 - metalness) * NdotL;
        
        vec3 ccF0 = mix(vec3(0.04), albedo.rgb, PBR_ClearCoat_Metalness);
        float ccRoughness = mix(0.03, 0.6, PBR_ClearCoat_SpecularRoughness);
        vec3 rawNormal = normalize(vNormal);
        float ccNdotH = max(0.0, dot(rawNormal, H));
        float ccNdotV = max(0.0, dot(rawNormal, -V));
        
        float ccDist = Distribution(ccNdotH, ccRoughness);
        vec3 ccFresnel = Fresnel(ccNdotV, ccF0) * PBR_ClearCoat_Strength;
        vec3 ccSpecular = ccDist * ccFresnel;
        if(i == 0){mainLight = clamp(dot(vNormal, L), 0.0, 1.0);}
        color += ((diffuse + specular * (1.0-ccFresnel)) * (1.0-ccFresnel) + ccSpecular) * DirectionalLightColor[i].rgb * PBR_LightColor.rgb * vColor.rgb * AO * cavity;
    }

#elif LIGHTS_DIRECTIONAL
    for (i = 0; i < LIGHTS_DIRECTIONAL; ++i)
    {
        vec3 L = vDirectionalLightDirection[i];
        vec3 H = normalize(-V + L);
        
        float NdotH = clamp(max(0.0, dot(N, H)), 0.0, 1.0);
        float NdotV = clamp(max(0.0, dot(N, -V)), 0.0, 1.0);
        float NdotL = clamp(max(0.0, dot(N, L)), 0.0, 1.0);
        float HdotV = clamp(max(0.0, dot(H, -V)), 0.0, 1.0);
        
        vec3 F0 = mix(vec3(0.04), albedo.rgb, metalness);
        float dist = Distribution(NdotH, roughness);
        float geo = Geometry(NdotV, NdotL, roughness);
        vec3 fresnel = Fresnel(HdotV, F0);
        vec3 specularNum = (dist * geo) * fresnel;
        float specularDenom = max(0.00016, 4.0 * NdotV * NdotH);
        vec3 specular = specularNum / specularDenom;
        vec3 diffuse =  ((1.0 / PI) *  albedo.rgb) * (1.0 - metalness) * NdotL;
        vec3 lightColor = (diffuse + specular) * DirectionalLightColor[i].rgb * PBR_LightColor.rgb;
        if(i == 0){mainLight = NdotL;}
        color += lightColor * vColor.rgb * AO * cavity;
        //color = ccRoughness;
    }
    
#endif

 
#if LIGHTS_POINT && CLEARCOAT
    for (i = 0; i < LIGHTS_POINT; ++i)
    {
         vec3 L = normalize(-vPointLightDirection[i]);
         vec3 H = normalize(-V + L);

         float NdotH = clamp(max(0.0, dot(N, H)), 0.0, 1.0);
         float NdotV = clamp(max(0.0, dot(N, -V)), 0.0, 1.0);
         float NdotL = clamp(max(0.0, dot(N, L)), 0.0, 1.0);
         float HdotV = clamp(max(0.0, dot(H, -V)), 0.0, 1.0);
        
         vec3 c = PointLightAttenuation[i];
         float d = length(vPointLightDirection[i]);
         float attenuation = 1.0 / (0.01 + c.x + c.y * d + c.z * d * d);
        vec3 F0 = mix(vec3(0.04), albedo.rgb, metalness);
         float dist = Distribution(NdotH, roughness);
         float geo = Geometry(NdotV, NdotL, roughness);
         vec3 fresnel = Fresnel(HdotV, F0);
        
         vec3 specularNum = (dist * geo) * fresnel;
         float specularDenom = max(0.000016, 4.0 * NdotV * NdotH);
         vec3 specular = specularNum / specularDenom;
         vec3 diffuse = (vec3(1.0) - fresnel) * albedo.rgb / PI * (1.0 - metalness) * NdotL;
        
        vec3 ccF0 = mix(vec3(0.04), albedo.rgb, PBR_ClearCoat_Metalness);
         float ccRoughness = mix(0.03, 0.6, PBR_ClearCoat_Roughness);
         vec3 rawNormal = normalize(vNormal);
         float ccNdotH = max(0.0, dot(rawNormal, H));
         float ccNdotV = max(0.0, dot(rawNormal, -V));
        
         float ccDist = Distribution(ccNdotH, ccRoughness);
         vec3 ccFresnel = Fresnel(ccNdotV, ccF0) * PBR_ClearCoat_Strength;
         vec3 ccSpecular = ccDist * ccFresnel;
        
        color += ((diffuse + specular * (1.0-ccFresnel)) * (1.0-ccFresnel) + ccSpecular) * PointLightColor[i].rgb * PBR_LightColor.rgb * vColor.rgb * attenuation * AO * cavity;
        
        //color = ccRoughness;
    }

#elif LIGHTS_POINT
    for (i = 0; i < LIGHTS_POINT; ++i)
    {
         vec3 L = normalize(-vPointLightDirection[i]);
         vec3 H = normalize(-V + L);

         float NdotH = clamp(max(0.0, dot(N, H)), 0.0, 1.0);
         float NdotV = clamp(max(0.0, dot(N, -V)), 0.0, 1.0);
         float NdotL = clamp(max(0.0, dot(N, L)), 0.0, 1.0);
         float HdotV = clamp(max(0.0, dot(H, -V)), 0.0, 1.0);
        
         vec3 c = PointLightAttenuation[i];
         float d = length(vPointLightDirection[i]);
         float attenuation = 1.0 / (0.01 + c.x + c.y * d + c.z * d * d);
        vec3 F0 = mix(vec3(0.04), albedo.rgb, metalness);
         float dist = Distribution(NdotH, roughness);
         float geo = Geometry(NdotV, NdotL, roughness);
         vec3 fresnel = Fresnel(HdotV, F0);
        
         vec3 specularNum = (dist * geo) * fresnel;
         float specularDenom = max(0.000016, 4.0 * NdotV * NdotH);
         vec3 specular = specularNum / specularDenom;
         vec3 diffuse = (vec3(1.0) - fresnel) * albedo.rgb / PI * (1.0 - metalness);
         vec3 lightColor = (diffuse + specular) * PointLightColor[i].rgb * PBR_LightColor.rgb * vColor.rgb * attenuation * NdotL;
        color += lightColor * AO * cavity;
    }
    
#endif

    color *= mix(1.0, max(mainLight, 0.0), PBR_HardShading);
    color += emissive * vColor.r * PBR_EmissiveIntensity;
    color *= BlendIntensity;
    outColor = vec4(Tonemap(color) + screenSpaceDither().rgb*5.0, BlendIntensity);
    
    //outColor = vec4(Tonemap(reflectionCube), 1.0);
    //outColor = vec4(normalize(vNormal), 1.0);
}