#version 330 core

#define PI 3.14159265359

out vec4 FragColor;

uniform vec2 u_resolution;
uniform float u_time;

vec3 colorA = vec3(0.912,0.568,0.436);
vec3 colorB = vec3(1.000,0.579,0.106);

float backInOut(float t) {
  float f = t < 0.5
    ? 2.0 * t
    : 1.0 - (2.0 * t - 1.0);

  float g = pow(f, 3.0) - f * sin(f * PI);

  return t < 0.5
    ? 0.5 * g
    : 0.5 * (1.0 - g) + 0.5;
}

void main() {
    vec3 color = vec3(0.0);

    float t = u_time * 0.05;
    float pct = backInOut( abs(fract(t) * 2.0-1.) );
 
    // float pct = abs(sin(u_time));

    // Mix uses pct (a value from 0-1) to
    // mix the two colors
    color = mix(colorA, colorB, pct);

    FragColor = vec4(color,1.0);
}