#type vertex
#version 330 core

layout(location = 0) in vec3 a_pos;
layout(location = 1) in vec4 a_color;

out vec4 v_color;

uniform mat4 u_viewProjectionMatrix;

void main() {
	v_color = a_color;
	gl_Position = vec4(a_pos, 1.f) * u_viewProjectionMatrix;
}

#type fragment
#version 330 core

layout(location = 0) out vec4 o_color;

in vec4 v_color;

void main() { o_color = v_color; }
