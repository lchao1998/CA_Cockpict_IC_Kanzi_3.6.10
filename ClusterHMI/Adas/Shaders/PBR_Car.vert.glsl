#version 300 es

precision highp float;

in  vec3 kzPosition;
in  vec3 kzNormal;
in  vec4 kzColor0;

uniform  mat4 kzProjectionCameraWorldMatrix;
uniform  mat4 kzWorldMatrix;
uniform  mat4 kzNormalMatrix;
uniform  vec3 kzCameraPosition;
uniform  float vColorAmount;
uniform  mat4 EnvironmentTransform;

out  vec3 vNormalRotated;
out  vec3 vNormal;
out  vec3 vViewDirection;
out  vec3 vViewDirectionRotated;
out  vec4 vColor;

#if TEXTURE_MODEL_ALBEDO || TEXTURE_MODEL_ROUGHNESS || TEXTURE_MODEL_METALNESS || TEXTURE_MODEL_NORMALMAP || TEXTURE_MODEL_OCCLUSION || TEXTURE_MODEL_EMISSIVE || TEXTURE_TILABLE_ALBEDO || TEXTURE_TILABLE_ROUGHNESS || TEXTURE_TILABLE_METALNESS || TEXTURE_TILABLE_NORMALMAP || TEXTURE_TILABLE_OCCLUSION || TEXTURE_TILABLE_EMISSIVE
in vec2 kzTextureCoordinate0;
uniform  vec4 TextureTransform;
#endif

#if (TEXTURE_TILABLE_EMISSIVE >= 2)
in vec2 kzTextureCoordinate1;
out  vec2 vTexCoord1;
#endif

#if TEXTURE_MODEL_ALBEDO || TEXTURE_MODEL_ROUGHNESS || TEXTURE_MODEL_METALNESS || TEXTURE_MODEL_NORMALMAP || TEXTURE_MODEL_OCCLUSION || TEXTURE_MODEL_EMISSIVE
out  vec2 vTexCoord;
#endif

#if TEXTURE_TILABLE_ALBEDO || TEXTURE_TILABLE_ROUGHNESS || TEXTURE_TILABLE_METALNESS || TEXTURE_TILABLE_NORMALMAP || TEXTURE_TILABLE_OCCLUSION || TEXTURE_TILABLE_EMISSIVE
uniform  vec2 PBR_TextureOffset;
uniform  vec2 PBR_TextureTiling;
out  vec2 vTilableCoord;
#endif

#if TEXTURE_MODEL_NORMALMAP || TEXTURE_TILABLE_NORMALMAP
in vec3 kzTangent;
out  vec3 vTangent;
out  vec3 vBinormal;
#endif

#if LIGHTS_DIRECTIONAL
uniform  vec3 DirectionalLightDirection[LIGHTS_DIRECTIONAL];
out  vec3 vDirectionalLightDirection[LIGHTS_DIRECTIONAL];
#endif

#if LIGHTS_POINT
uniform  vec3 PointLightPosition[LIGHTS_POINT];
out  vec3 vPointLightDirection[LIGHTS_POINT];
#endif

#if LIGHTS_SPOT
uniform  vec3 SpotLightPosition[LIGHTS_SPOT];
out  vec3 vSpotLightDirection[LIGHTS_SPOT];
#endif

void main()
{

    vec4 positionWorld = kzWorldMatrix * vec4(kzPosition.xyz, 1.0);
    vViewDirection = positionWorld.xyz - kzCameraPosition;
    vViewDirectionRotated =  (EnvironmentTransform * vec4(vViewDirection.xyz, 0.0)).xyz;
    
    vec4 N = kzNormalMatrix * vec4(kzNormal, 0.0);
    vNormal = N.xyz;
    vNormalRotated =  (EnvironmentTransform * N).xyz;
    
    float vcolorR = max(kzColor0.r, 0.0);
    vColor = pow(mix(vec4(1.0), vec4(vec3(vcolorR), 1.0), vColorAmount), vec4(2.2));
    
#if LIGHTS_DIRECTIONAL || LIGHTS_POINT || LIGHTS_SPOT
    int i;
#endif

#if LIGHTS_DIRECTIONAL
    for (i = 0; i < LIGHTS_DIRECTIONAL; ++i)
    {
        vDirectionalLightDirection[i] = normalize(-DirectionalLightDirection[i]);
    }
#endif

#if LIGHTS_POINT
    for (i = 0; i < LIGHTS_POINT; ++i)
    {
        vPointLightDirection[i] = positionWorld.xyz - PointLightPosition[i];
    }
#endif

#if LIGHTS_SPOT
    for (i = 0; i < LIGHTS_SPOT; ++i)
    {
        vSpotLightDirection[i] = positionWorld.xyz - SpotLightPosition[i];
    }
#endif

#if TEXTURE_MODEL_NORMALMAP || TEXTURE_TILABLE_NORMALMAP
    vTangent = (kzNormalMatrix * vec4(kzTangent.xyz, 0.0)).xyz;
    vBinormal = cross(vNormal, vTangent);
#endif
    
#if TEXTURE_MODEL_ALBEDO || TEXTURE_MODEL_ROUGHNESS || TEXTURE_MODEL_METALNESS || TEXTURE_MODEL_NORMALMAP || TEXTURE_MODEL_OCCLUSION || TEXTURE_MODEL_EMISSIVE
    vTexCoord = kzTextureCoordinate0 * TextureTransform.xy + TextureTransform.zw;
#endif

#if (TEXTURE_TILABLE_EMISSIVE >= 2)
    vTexCoord1 = kzTextureCoordinate1;
#endif

#if TEXTURE_TILABLE_ALBEDO || TEXTURE_TILABLE_ROUGHNESS || TEXTURE_TILABLE_METALNESS || TEXTURE_TILABLE_NORMALMAP || TEXTURE_TILABLE_OCCLUSION || TEXTURE_TILABLE_EMISSIVE
    vTilableCoord = kzTextureCoordinate0 * PBR_TextureTiling + PBR_TextureOffset;
#endif

    gl_Position = kzProjectionCameraWorldMatrix * vec4(kzPosition.xyz, 1.0);
}