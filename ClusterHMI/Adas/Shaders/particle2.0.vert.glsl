#define M_2_PI 6.28318530
precision highp float;

attribute vec3 kzPosition;
attribute vec2 kzTextureCoordinate0;

uniform highp mat4 kzProjectionCameraWorldMatrix;
uniform  vec4 TextureTransform;
uniform  lowp float Curvature;

varying mediump vec2 vTexCoord;


 mat4 rotate2d(float _angle){
   float angle = radians(_angle);//角度转为弧度
   return mat4(cos(angle),0.0,sin(angle),0.0,
               0.0,1.0,0.0,0.0,
               -sin(angle),0,cos(angle),0.0,
               0.0,0.0,0.0,1.0
               );
 }

void main()
{
    precision mediump float;
    
    vec4 pos = vec4(kzPosition.xyz, 1.0);
   
  
    
    vTexCoord = kzTextureCoordinate0 * TextureTransform.xy + TextureTransform.zw;
    gl_Position = kzProjectionCameraWorldMatrix * vec4( pos.xyz, 1.0);
}