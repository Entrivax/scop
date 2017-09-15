#version 400

layout(location = 0) in vec3 vp;
layout(location = 1) in vec2 uvIn;

uniform mat4 projection;
uniform mat4 modelview;

out float dist;
out vec2 uv;

void main() {
	vec4 cs_pos = modelview * vec4(vp, 1.0);
	dist = cs_pos.z;
	uv = uvIn;
	gl_Position = projection * cs_pos;
}