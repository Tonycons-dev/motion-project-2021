#version 330

in vec3 vertexPosition;
out vec3 fragPosition;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 mvp;

void main()
{
    fragPosition = vertexPosition;

    mat4 rotView = mat4(mat3(view));
    vec4 clipPos = projection * rotView * vec4(vertexPosition, 1.0);

    gl_Position = clipPos.xyzw;
}