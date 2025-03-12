#version 330

in vec3 vertexPosition;
out vec3 fragPosition;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    fragPosition = vertexPosition;
    gl_Position = projection*view*vec4(vertexPosition, 1.0);
}