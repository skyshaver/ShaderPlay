// circles!
// this one is more pumping

#version 330 core

#ifdef GL_ES
precision mediump float;
#endif

out vec4 FragColor;
uniform vec2 u_resolution;
uniform vec2 u_mousePos;
uniform float u_time;


void main(){
	vec2 st = gl_FragCoord.xy/u_resolution;
    float pct = 0.0;

    // a. The DISTANCE from the pixel to the center
    // * 2.0 - 0.5 scales it down to fit in the window
    // pumping breathing
    // pct = distance(st * (abs(sin(u_time * 0.5)) + 1) - 0.01, vec2(0.1 * abs(sin(u_time * 0.5)) + 0.5));


    // different pct funcs

    // more diffuse spread, works great with crazy clouds
    pct = distance(st,vec2(0.4)) + distance(st,vec2(0.6));

    // much darker, denser spread
    // pct = distance(st,vec2(0.4)) * distance(st,vec2(0.6));

    // fairly diffuse and bisected
    // pct = min(distance(st,vec2(0.4)),distance(st,vec2(0.6)));
    
    // centred around diagonal axis
    // pct = max(distance(st,vec2(0.4)),distance(st,vec2(0.6)));

    // two centers, one dark, one light
    // pct = pow(distance(st,vec2(0.4)),distance(st,vec2(0.6)));

    // vec3 color = vec3(pct);

    // this makes a blue cloud?
    //vec3 color = vec3(pct,1,1);

    // crazy clouds
    vec3 color = vec3(pct,abs(sin(u_time * 0.1)), 1);
    
	FragColor = vec4( color, 1.0 );
}