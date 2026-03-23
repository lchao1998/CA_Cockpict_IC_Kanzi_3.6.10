precision mediump float;

uniform float BlendIntensity;

uniform float SCALE ;//比例
uniform float SPEED ;
uniform float LENGTH ;//长度

uniform mediump float kzTime;
varying mediump vec2 vTexCoord;

void main()
{

vec3 col2=vec3(0.0);
    for(float j = 0.0; j < 5.0; j++){
    vec2 uv2 =vTexCoord;
    //Y-axis movement
    uv2.y-=j*0.2;
    uv2.x-=1.;
    //X-axis movement
    uv2.x+=fract((SPEED+0.5)*kzTime+j*0.3);
    
    //stretching UV
    uv2.x=uv2.x/LENGTH;
    uv2.y=uv2.y/SCALE*100.;
    
    //Limit the UV length to 0 to 1
    float d=1.-smoothstep(0.,1.,length(uv2));
 
    col2 +=vec3(1.0, 0.55, 0.25) * d*3.;
    }
  	col2=col2;
    
	//repeat
    vec3 col3=vec3(0.0);
    for(float j = 0.0; j < 8.0; j++){
    vec2 uv2 =vTexCoord;
    uv2.y-=j*0.125;
    uv2.x-=1.;
    uv2.x+=fract((SPEED+0.2)*kzTime+j*0.3);
    
    uv2.x=uv2.x/LENGTH;
    uv2.y=uv2.y/SCALE*100.;
    
    float d=1.-smoothstep(0.,1.,length(uv2));
 
    col3 +=vec3(0.35, 0.65, 1.0)* d*1.3;
    }
  	col3=col3;
    
     
    gl_FragColor = vec4(vec3(col2+col3),1.0) * BlendIntensity;
}