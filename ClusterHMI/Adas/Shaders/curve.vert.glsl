attribute vec3 kzPosition;
attribute vec2 kzTextureCoordinate0;
uniform highp mat4 kzProjectionCameraMatrix;
uniform highp mat4 kzProjectionCameraWorldMatrix;
uniform highp mat4 kzWorldMatrix;

uniform mediump vec2 CurTextureOffset;
uniform mediump vec2 CurTextureTiling;
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
    pos *= rotate2d(90.0);
    
    float x = pos.x;
   
    float y = pos.y;
    
    float a = Curvature*0.000001;
    
    float z ;
    if(x<-120.0){
    z =  pos.z+a*(x+10.0*12.5)*(x+10.0*12.5)*(x+10.0*12.5);}
    else{
    z = pos.z+a*(-120.0+10.0*12.5)*(-120.0+10.0*12.5)*(-120.0+10.0*12.5);}
   
  
    pos=vec4(x,y,z,1.0);
    vTexCoord = kzTextureCoordinate0 * CurTextureTiling + CurTextureOffset;
    gl_Position = kzProjectionCameraWorldMatrix * vec4(pos.xyz, 1.0);
}