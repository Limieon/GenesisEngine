#type vertex
#version 330 core

layout(location = 0) in vec3 a_pos;
layout(location = 1) in vec2 a_uv;
layout(location = 2) in vec4 a_color;
layout(location = 3) in vec2 a_tiling;

uniform mat4 u_viewProjectionMatrix;

out vec2 v_uv;
out vec4 v_color;
out vec2 v_tiling;

void main() {
	v_uv = a_uv;
	v_color = a_color;
	v_tiling = a_tiling;
	gl_Position = u_viewProjectionMatrix * vec4(a_pos, 1.f);
}

#type fragment
#version 330 core

layout(location = 0) out vec4 o_color;

in vec2 v_uv;
in vec4 v_color;
in vec2 v_tiling;

uniform sampler2D u_texture;

void main() {
	o_color = texture(u_texture, v_uv * v_tiling) * v_color;
	// o_color = vec4(v_uv.x, v_uv.y, 0.f, 1.f);
}
