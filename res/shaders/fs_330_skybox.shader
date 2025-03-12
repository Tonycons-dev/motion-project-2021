#version 330

in vec3 fragPosition;
out vec4 finalColor;

uniform samplerCube envMap;
uniform bool vFlipped;
uniform bool useGamma;

void main()
{
    vec3 color = vec3(0.0);

    if (vFlipped)
        color = texture(envMap, vec3(fragPosition.x, -fragPosition.y, fragPosition.z)).rgb;
    else
        color = texture(envMap, fragPosition).rgb;

    if (useGamma)
    {
        color = color / (color + vec3(1.0));
        color = pow(color, vec3(1.0 / 2.2));
    }

    finalColor = vec4(color, 1.0);
}
