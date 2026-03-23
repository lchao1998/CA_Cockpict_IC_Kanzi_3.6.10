#define M_2_PI 6.28318530
precision highp float;

uniform float BlendIntensity;

uniform float SCALE ;//比例
uniform float SPEED ;
uniform float INTENSITY ;//强度
uniform float LENGTH ;//长度
uniform float RADIUS ;//半径
uniform float FADING ;//衰退
uniform float GLOW ;//发光

uniform mediump float kzTime;
varying mediump vec2 vTexCoord;

vec2 sdBezier(vec2 pos, vec2 A, vec2 B, vec2 C)
{    
    vec2 a = B - A;
    vec2 b = A - 2.0*B + C;
    vec2 c = a * 2.0;
    vec2 d = A - pos;

    float kk = 1.0 / dot(b,b);
    float kx = kk * dot(a,b);
    float ky = kk * (2.0*dot(a,a)+dot(d,b)) / 3.0;
    float kz = kk * dot(d,a);      

    vec2 res;

    float p = ky - kx*kx;
    float p3 = p*p*p;
    float q = kx*(2.0*kx*kx - 3.0*ky) + kz;
    float h = q*q + 4.0*p3;

    h = sqrt(h);
    vec2 x = (vec2(h, -h) - q) / 2.0;
    vec2 uv = sign(x)*pow(abs(x), vec2(1.0/3.0));
    float t = clamp(uv.x+uv.y-kx, 0.0, 1.0);

    return vec2(length(d+(c+b*t)*t),t);
}

//圆形状
vec2 circle(float t){
    float x = SCALE * (t-5.0);
    float y = SCALE *0.0001*(t-5.0)*(t-5.0);
    return vec2(x, y);
}



//pos为uv（中心点），sp为速度
float mapcircle(vec2 pos,float sp){
    float t = fract(-SPEED *kzTime*sp);//整数部分取小数，负数部分取小数+1（0，1）
    float dl = LENGTH/ INTENSITY;//  长度/强度_线段长度，并逐渐显现出越来越圆
    vec2 p1 = circle(t * M_2_PI);
    vec2 p2 = circle((dl+ t) * M_2_PI);
    vec2 c = (p1 + p2) / 2.0;
    float d = 1e9;
    
    for(float i = 2.0; i < INTENSITY; i++){
        p1 = p2;
        p2 = circle((i * dl + t) * M_2_PI);
        vec2 c_prev = c;
        c = (p1 + p2) / 2.;
        vec2 f = sdBezier(pos, c_prev, p1, c);
        d = min(d, f.x +0.015* (f.y + i) / INTENSITY);
    }
    return d;
}

void main()
{
precision mediump float;

    vec3 col1 = vec3(0.0);
    for( float j = 0.0; j < 8.0; j++){
    vec2 uv =vTexCoord;
    uv.y-=j/8.0;
    uv.x-=1.0;
    uv.x+=cos(kzTime+j);
    
    float dist1 = mapcircle(uv.xy*vec2(1.0,1.0),1.0);
    vec3 col11 = vec3(0.1, 0.3, 1.00) * pow(RADIUS/dist1, GLOW);
    col1 = col1+ (col11/2.0);
    }
    col1=col1;
    
    
     vec3 col2 = vec3(0.0);
    for( float j = 0.0; j < 5.0; j++){
    vec2 uv2 =vTexCoord;
    uv2.y-=j/5.0+0.3;
    uv2.x-=1.5;
    uv2.x+=cos(kzTime+j);
    
    float dist2 = mapcircle(uv2.xy*vec2(1.0,1.0),1.0);
    vec3 col22 = vec3(1.0, 0.5,0.2) * pow(RADIUS/dist2, GLOW);
    col2 = col2+ (col22/2.0);
    }
    col2=col2;
    
   
     
    gl_FragColor = vec4(vec3(col1+col2),1.0) * BlendIntensity;
}
