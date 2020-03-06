// this one is a very pretty transition full of orange and pink

#version 330 core

#define PI 3.14159265359

out vec4 FragColor;

uniform vec2 u_resolution;
uniform vec2 u_mousePos;
uniform float u_time;

vec3 colorA = vec3(0.812,0.168,0.436);
vec3 colorB = vec3(1.000,0.579,0.106);

float plot (vec2 st, float pct){
  return  smoothstep( pct-0.01, pct, st.y) -
          smoothstep( pct, pct+0.01, st.y);
}

void main() {
    vec2 st = gl_FragCoord.xy/u_resolution.xy;
    vec3 color = vec3(0.0);

    vec3 pct = vec3(st.x);

    pct.r = smoothstep(0.0,1.0, st.x) * (sin(u_time) * .5);
    pct.g = sin(st.x*PI) * (sin(u_time) * .5);
    pct.b = pow(st.x,0.5) * (sin(u_time) * .5);

    color = mix(colorA, colorB, pct);

    // Plot transition lines for each channel
    // color = mix(color,vec3(1.0,0.0,0.0),plot(st,pct.r));
    // color = mix(color,vec3(0.0,1.0,0.0),plot(st,pct.g));
    // color = mix(color,vec3(0.0,0.0,1.0),plot(st,pct.b));

    FragColor = vec4(color,1.0);
}