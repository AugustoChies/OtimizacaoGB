#version 400

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_normal;
layout (location = 2) in vec3 vertex_colour;
layout (location = 3) in vec2 texcoord;



uniform mat4 view, proj,model;

out vec3 colour, position_eye, normal_eye;


void main() {
	colour = vertex_colour;
	position_eye = vec3 (view * model *  vec4 (vertex_position, 1.0));
	normal_eye = vec3 (view * model * vec4 (vertex_normal, 0.0));
	//gl_Position = proj * vec4 (position_eye, 1.0);
	gl_Position = proj * view * vec4 (vertex_position, 1.0);
}
