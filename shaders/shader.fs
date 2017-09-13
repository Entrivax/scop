#version 400

out vec4 frag_colour;

in float dist;

void main() {
	float color = clamp(1.0 / dist, 0.0, 1.0);
	frag_colour = vec4(color, color, color, 1.0);
}