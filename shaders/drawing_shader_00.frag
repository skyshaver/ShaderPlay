// draw a couple of rectangles

#version 330 core

out vec4 FragColor;
uniform vec2 u_resolution;
uniform vec2 u_mousePos;
uniform float u_time;

// 4.5.
bool isinrec(vec2 bl, vec2 tr, vec2 st)
{
    vec2 s1 = step(bl,st);
    vec2 s2 = step(tr,1.0-st);
    return s1.x * s1.y * s2.x * s2.y == 0.0 ? false : true;
}

void main(){
    vec2 st = gl_FragCoord.xy/u_resolution.xy;
    vec3 color = vec3(0.0);
 

    // 1.2.
	float proportion = 0.1;
    vec2 bl = smoothstep(vec2(0.0), vec2(proportion),st);
    vec2 tr = smoothstep(vec2(0.0), vec2(proportion),1.0-st);

    // 3.
    // vec2 bl = floor(st*2.0);
    // vec2 tr = floor(8.0*(1.0-st));

    float pct = bl.x * bl.y * tr.x * tr.y;
    color = vec3(pct);

    // 6.
    // vec2 bl = vec2(0.2, 0.4);
    // vec2 tr = vec2(0.1, 0.3);
    
    // vec2 bl1 = vec2(0.1, 0.1);
    // vec2 tr1 = vec2(0.35, 0.65);

    // if(isinrec(bl, tr, st))
    //     color = vec3(0.9,0.6,0.3);
    
    // if(isinrec(bl1, tr1, st))
    //     color = vec3(0.1, 0.1, 0.7);

    FragColor = vec4(color,1.0);
}