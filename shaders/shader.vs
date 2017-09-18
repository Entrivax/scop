#version 400

layout(location = 0) in vec3 vp;
layout(location = 1) in vec2 uvIn;

uniform mat4 projection;
uniform mat4 modelview;

out float dist;
out vec4 viewspace;
out vec2 uv;

void main() {
	viewspace = modelview * vec4(vp, 1.0);
	dist = viewspace.z;
	uv = uvIn;
	gl_Position = projection * viewspace;
}