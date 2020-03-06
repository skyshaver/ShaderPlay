#version 330 core

#define PI 3.14159265359

out vec4 FragColor;

uniform vec2 u_resolution;
uniform vec2 u_mousePos;
uniform float u_time;

// Plot a line on Y using a value between 0.0-1.0
float plot(vec2 st, float pct){
  return  smoothstep( pct-0.02, pct, st.y) -
          smoothstep( pct, pct+0.02, st.y);
}

void main() {
	vec2 st = gl_FragCoord.xy/u_resolution;
	vec2 mp = u_mousePos/u_resolution;

	// time bends the line
    // float y = pow(st.x, sin(u_time) + 1);

    // mouse bends the line
    // float y = pow(st.x, sin(mp.x) * PI);

    // float y = log(0.8);

    // Smooth interpolation between 0.1 and 0.9
    // fun with time
    // float y = smoothstep(sin(u_time),sin(u_time) + 1,st.x);

    // float y = smoothstep(0.2,0.5,st.x) - smoothstep(0.5,0.8,st.x);

    // slowly compressing sine wave
    // float y = sin(st.x * u_time) / 2 + 0.5;

    //float y = cos(st.x * u_time) / 2 + 0.5;

    float y = pow(abs(st.x) , 0.5);

    vec3 color = vec3(y);

    // Plot a line
    float pct = plot(st,y);
    color = (1.0-pct)*color+pct*vec3(0.0,1.0,0.0);

	FragColor = vec4(color,1.0);
}