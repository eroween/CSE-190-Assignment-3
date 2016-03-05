attribute vec3 vertex_position;
attribute vec3 vertex_color;
attribute vec3 vertex_normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

varying vec3 fragment_color;
varying vec3 fragment_normal;

void main()
{
    fragment_color = vertex_color;
    fragment_normal = vertex_normal;
    gl_Position = projection * view * model * vec4(vertex_position, 1.0);
}
