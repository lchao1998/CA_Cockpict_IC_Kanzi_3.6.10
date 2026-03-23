#define M_2_PI 6.283
precision highp float;

attribute vec3 kzPosition;
attribute vec2 kzTextureCoordinate0;

uniform highp mat4 kzProjectionCameraWorldMatrix;
uniform  vec4 TextureTransform;
uniform  lowp float Curvature;

varying mediump vec2 vTexCoord;

void main()
{
    precision highp float;
    
    vec4 pos = vec4(kzPosition.xyz, 1.0);
  
    
    vTexCoord = kzTextureCoordinate0 * TextureTransform.xy + TextureTransform.zw;
    gl_Position = kzProjectionCameraWorldMatrix * vec4( pos.xyz, 1.0);
}