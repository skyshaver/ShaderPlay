// circles!
// this one is super beuatiful, like breathing clouds
#version 330 core

out vec4 FragColor;
uniform vec2 u_resolution;
uniform vec2 u_mousePos;
uniform float u_time;


void main(){
	vec2 st = gl_FragCoord.xy/u_resolution;
    float pct = 0.0;

    // a. The DISTANCE from the pixel to the center
    // * 2.0 - 0.5 scales it down to fit in the window
    pct = distance(st * 2.0 - 0.5, vec2(0.5));

    // vec3 color = vec3(pct);

    // this makes a blue cloud?
    // vec3 color = vec3(pct,1,1);

    vec3 color = vec3(pct,abs(sin(u_time * 0.1)), 1);
    
	FragColor = vec4( color, 1.0 );
}