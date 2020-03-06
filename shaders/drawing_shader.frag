#version 330 core

#define PI 3.14159265359
#define TWO_PI 6.28318530718

out vec4 FragColor;

uniform vec2 u_resolution;
uniform float u_time;

void main(){
    vec2 st = gl_FragCoord.xy/u_resolution.xy;
    vec3 color = vec3(0.0);

    // bottom-left
    // vec2 bl = vec2(0.2, 0.4);
    vec2 bl = step(vec2(0.1), st * 0.2);
    float pct = bl.x * bl.y;

    // top-right
    // vec2 tr = vec2(0.1, 0.3); 
    vec2 tr = step(vec2(0.1), 1.0 - st);
    pct *= tr.x * tr.y;

    color = vec3(pct);

    FragColor = vec4(color,1.0);
}