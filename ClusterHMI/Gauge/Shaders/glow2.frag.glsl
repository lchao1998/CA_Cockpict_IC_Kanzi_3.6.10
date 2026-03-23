precision highp float;

uniform float BlendIntensity;
uniform mediump float kzTime;
uniform vec2 i;
uniform float grow2;

varying vec2 vTexCoord;

#define M_PI 3.1415926535897932384626433832795
#define M_TWO_PI (2.0 * M_PI)

float rand(vec2 n) {
    return fract(sin(dot(n, vec2(12.9898,12.1414))) * 83758.5453);
}

float noise(vec2 n) {
    const vec2 d = vec2(0.0, 1.0);
    vec2 b = floor(n);
    vec2 f = smoothstep(vec2(0.0), vec2(0.5), fract(n));
    return mix(mix(rand(b), rand(b + d.yx), f.x), mix(rand(b + d.xy), rand(b + d.yy), f.x), f.y);
}

vec3 ramp(float t) {
    return t <= 0.5 ?  vec3( 0.05*(0.2 - t * 0.5), .1, 1.2 ) / t : vec3( .05 * (1. - t) * 2., .15, 0.4 ) / t;
}
vec2 polarMap(vec2 uv, float shift, float inner) {

    uv = vec2(0.5) - uv;
    
    
    float px = 1.0 - fract(atan(uv.y, uv.x) / 6.28 + 0.25) + shift;
    float py = (sqrt(uv.x * uv.x + uv.y * uv.y) * (1.0 + inner * 2.0) - inner) * 2.0;
    
    return vec2(px, py);
}
float fire(vec2 n) {
    return noise(n) + noise(n * 2.1) * .6 + noise(n * 5.4) * .42;
}

float shade(vec2 uv, float t) {
    uv.x += uv.y < .5 ? 23.0 + t * .035 : -11.0 + t * .03;    
    uv.y = abs(uv.y - .5);
    uv.x *= 35.0;
    
    float q = fire(uv - t * .013) / 2.0;
    vec2 r = vec2(fire(uv + q / 2.0 + t - uv.x - uv.y), fire(uv + q - t));
    
    return pow((r.y + r.y) * max(.0, uv.y) + .1, 4.0);
}

vec3 color(float grad) {
    
     float m2 =-(grow2)*-(grow2)*1.5;
    grad =sqrt(grad);
    vec3 color = ramp(grad)-0.1;
    color /= (m2 + max(vec3(0), color));
    
    return color;

}


void main()
{
    precision highp float;
    
    float t = kzTime;
    vec2 uv = vTexCoord-0.1 ;
    float ff = -uv.y+1.0;
    vec2 uv2 = uv;
    uv2.y = 1.0 - uv2.y;
       uv = polarMap(uv, 1.3, 3.);
       uv2 = polarMap(uv2, 1.9, 3.);

    vec3 c1 = color(shade(uv, t)) * ff;
    vec3 c2 = color(shade(uv2, t)) * (1.0 - ff);
    
    
    vec2 uv3 = vTexCoord-0.1;
    uv3-=0.5;
    uv3.x *= 1.0;
    uv3.y-=0.5;
 
    float d = length(uv3);
    float r = 0.4;
    float c = smoothstep(r, r + 0.2, d);
    vec3 dd =vec3(c);
    
   vec4 fragColor = vec4((c1+c2)*dd , 1.0);
    
    gl_FragColor = fragColor;
}