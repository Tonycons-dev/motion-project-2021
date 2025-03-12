#version 330

#define MAX_LIGHTS        4
#define LIGHT_DIRECTIONAL 0
#define LIGHT_POINT       1

struct MaterialProperty
{
    vec3 color;
    int useSampler;
    sampler2D sampler;
};

struct Light
{
    int enabled;
    int type;
    vec3 position;
    vec3 target;
    vec4 color;
};

in vec2 fragTexCoord;
in vec4 fragColor;
in vec3 fragPosition;
in vec3 fragNormal;

out vec4 finalColor;

uniform sampler2D texture0;
uniform vec4 colDiffuse;
uniform Light lights[MAX_LIGHTS];
uniform vec4 ambient;
uniform vec3 viewPos;
uniform float fogDensity;
uniform int fogEnabled;

void fogTechnique(
    vec4 texelColor, vec3 lightDot, vec3 normal, vec3 viewDir, vec3 specular)
{
    for (int i = 0; i < MAX_LIGHTS; i++)
    {
        if (lights[i].enabled)
        {
            vec3 light = vec3(0.0);

            if (lights[i].type == LIGHT_DIRECTIONAL)
                light = -normalize(lights[i].target - lights[i].position);

            if (lights[i].type == LIGHT_POINT)
                light = normalize(lights[i].position - fragPosition);

            float NdotL = max(dot(normal, light), 0.0);
            lightDot += lights[i].color.rgb*NdotL;

            float specColor = 0.0;

            if (NdotL > 0.0)
                specColor = pow(max(0.0, dot(viewD, reflect(-(light), normal))), 16.0);

            specular += specColor;
        }
    }
    finalColor = (texelColor*((colDiffuse + vec4(specular,1))*vec4(lightDot, 1.0)));
    finalColor += texelColor*(ambient/10.0);

    finalColor = pow(finalColor, vec4(1.0/2.2));
    float dist = length(viewPos - fragPosition);

    const vec4 fogColor = vec4(0.5, 0.5, 0.5, 1.0);
    float fogFactor = 1.0/exp((dist*fogDensity)*(dist*fogDensity));

    fogFactor = clamp(fogFactor, 0.0, 1.0);
    finalColor = mix(fogColor, finalColor, fogFactor);
}

void main()
{
    vec4 texelColor = texture(texture0, fragTexCoord);
    vec3 lightDot   = vec3(0.0);
    vec3 normal     = normalize(fragNormal);
    vec3 viewDir    = normalize(viewPos - fragPosition);
    vec3 specular   = vec3(0.0);

    finalColor = vec4(texelColor, 1.0);

    if (fogEnabled == 1)
        fogTechnique(texelColor, lightDot, normal, viewDir, specular);
}