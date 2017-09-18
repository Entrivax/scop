#version 400

#define FOG 1
#define FOG_START 10
#define FOG_END 20

out vec4 frag_colour;

in vec2 uv;
in vec4 viewspace;
in float dist;

uniform float mode;
uniform sampler2D tex;

void main() {

	float color = 0.15 + ((gl_PrimitiveID % 9 + 1) / 9.0) / 0.85;
	vec4 grey = vec4(color, color, color, 1.0);

#if FOG == 1
	float d = length(viewspace);
	float fogFactor = clamp((FOG_END - d) / (FOG_END - FOG_START), 0.0, 1.0);
	frag_colour = mix(grey, mix(vec4(0, 0, 0, 1), texture(tex, uv), fogFactor), mode);
#else
	frag_colour = mix(grey, texture(tex, uv), mode);
#endif

}