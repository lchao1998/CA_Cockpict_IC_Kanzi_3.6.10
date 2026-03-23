#define M_PI 3.141592653589793

precision mediump float;

uniform sampler2D Texture;
uniform sampler2D Texture1;
uniform float BlendIntensity;
uniform float value;

varying vec2 vTexCoord;

void main()
{
    vec4 pattern = texture2D(Texture, vTexCoord);
    vec4 fill = texture2D(Texture1, vTexCoord);
    
    lowp vec2 pos = vec2(vTexCoord.x - 0.5, vTexCoord.y-0.5);
    
    
    lowp float d = length(pos);
    //
    lowp float angle = atan(pos.x, pos.y)/  (2.0 * M_PI);
    lowp float v = 0.66*value-0.33;

    //
    float dd=length(smoothstep(v, v + 0.1, angle));//v用于改变’颜色'
    lowp vec4 color = mix(pattern, vec4(0.0),smoothstep(v, v + 0.1, angle)) ;//蒙蔽 黑色显示
    
    // 
    float ddd=length(step(v, angle));
    color += mix(fill, vec4(0.0), step(v, angle));

    color = mix(vec4(0.0), color, smoothstep(0.193 - 0.001, 0.193 + 0.001, d));//蒙版
    
    gl_FragColor=vec4(vec3(color),1.0);
}
