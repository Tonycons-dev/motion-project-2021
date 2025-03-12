#version 100

precision mediump float;
varying vec3 fragPosition;

uniform samplerCube envMap;
uniform bool vFlipped;
uniform bool useGamma;

void main()
{
    vec4 texelColor = vec4(0.0);

    if (vFlipped)
        texelColor = textureCube(envMap, vec3(fragPosition.x, -fragPosition.y, fragPosition.z));
    else
        texelColor = textureCube(envMap, fragPosition);

    vec3 color = vec3(texelColor.x, texelColor.y, texelColor.z);

    if (useGamma)
    {
        color = color / (color + vec3(1.0));
        color = pow(color, vec3(1.0 / 2.2));
    }

    gl_FragColor = vec4(color, 1.0);
}
