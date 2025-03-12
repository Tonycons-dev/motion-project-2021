#version 100

attribute vec3 vertexPosition;
varying vec3 fragPosition;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    fragPosition = vertexPosition;

    mat4 rotView = mat4(mat3(view));
    vec4 clipPos = projection * rotView * vec4(vertexPosition, 1.0);

    gl_Position = clipPos.xyzw;
}