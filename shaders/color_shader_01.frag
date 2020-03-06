// cartestian color wheel
#version 330 core

#define PI 3.14159265359
#define TWO_PI 6.28318530718

out vec4 FragColor;

uniform vec2 u_resolution;
uniform float u_time;

//  Function from Iñigo Quiles
//  https://www.shadertoy.com/view/MsS3Wc
vec3 hsb2rgb( in vec3 c ){
    vec3 rgb = clamp(abs(mod(c.x * 6.0 + vec3(0.0,4.0,2.0),
                             6.0) -3.0) -1.0,
                     0.0,
                     1.0 );
    rgb = rgb * rgb * (3.0 - 2.0 * rgb);
    return c.z * mix(vec3(1.0), rgb, c.y);
}

void main(){
    vec2 st = gl_FragCoord.xy/u_resolution;
    vec3 color = vec3(0.0);

    // Use polar coordinates instead of cartesian
    // uncomment the u_time for an interesting motion effect, 
    // can't figure out how to make it spin though EDIT: add instead of multiply
    vec2 toCenter = vec2(0.5) - st;
    float angle = atan(toCenter.y, toCenter.x); //* sin(u_time);
    float radius = length(toCenter) * 2.0;

    // Map the angle (-PI to PI) to the Hue (from 0 to 1)
    // and the Saturation to the radius
    // adding time to the angle makes it spin
    color = hsb2rgb(vec3(((angle / TWO_PI) + 0.5) + (u_time * 0.1), radius, 1));

    FragColor = vec4(color, 1.0);
}