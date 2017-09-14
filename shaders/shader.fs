#version 400

#define FOG 0

out vec4 frag_colour;

in float dist;

void main() {
	//float color = clamp(1.0 / dist, 0.0, 1.0);
	float color = 0.15 + ((gl_PrimitiveID % 9 + 1) / 9.0) / 0.85;
#if FOG == 1
	color /= max(dist, 1.0);
#endif
	frag_colour = vec4(color, color, color, 1.0);
}