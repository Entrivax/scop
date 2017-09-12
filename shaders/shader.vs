#version 400

in vec3 vp;

uniform mat4 projection;
uniform mat4 modelview;

out float dist;

void main() {
	vec4 cs_pos = modelview * vec4(vp, 1.0);
	dist = -cs_pos.y;
	gl_Position = projection * cs_pos;
}